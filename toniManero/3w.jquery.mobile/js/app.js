__pwmSetRequest = function (channel, dutty, id)
//{"jsonrpc": "2.0", "method": "pwmSet", "params": {"channel": 23, "dutty": 42}, "id": 4}
{
	this.jsonrpc = "2.0";
	this.method =  "pwmSet";
	this.params = {"channel": 0, "dutty": 0};
	this.id = id;
	
	this.params.channel = channel;
	this.params.dutty = dutty;
}	
	
appData = function()
{
	__data = function ()
	{
		this.m_targetIp = "0.0.0.0";
		this.m_targetPort = 80;
		this.m_channelCount = 2;
		this.a_channelPwm = [50,50,50,50, 50,50,50,50, 50,50,50,50, 50,50,50,50];
	}
	
	this.s_data = new __data();
	
	this.checkConfig = function ()
	{
		var local = localStorage.getItem("toniManero.data");
		if(local === null)
		{
			return 0;			
		}
		else
		{
			return 1;
		}
	}
	
	this.checkDefault = function ()
	{
		if(this.s_data.m_targetIp == "0.0.0.0")
		{
			return 1;			
		}
		else
		{
			return 0;
		}
	}
	
	this.load = function ()
	{
		var js = localStorage.getItem("toniManero.data");
		this.s_data = JSON.parse(js);
	}
	
	this.save = function ()
	{		
		var js = JSON.stringify(this.s_data);
		localStorage.setItem("toniManero.data", js);
	}
}

var gData = new appData();
var gRpcUrl = "json.rpc";
var gSliderContainer = "#sliderContainer";
var gSliderTemplate  = '<div class="ui-field-contain">';
	gSliderTemplate += '<label for="###slider_Input_Id###">###slider_Channel###</label>';
	gSliderTemplate += '<input id="###slider_Input_Id###" name="slider" class="custom-slider" channel-number="###channel_number###" value="###slider_Value###" min="0" max="100" type="range" data-highlight="true">';		 
    gSliderTemplate += '</div>';
					 		
$( document ).ready(function()
{
   if(gData.checkConfig())
   {
		gData.load();
   }
   else
   {
	   gData.save();
   }
   
   guiBuild();
   guiUpdate();
   guiEventsInit();
   
   if(gData.checkDefault())
   {
	   $( "#settingsPannel" ).trigger( "expand" );							
   }
   
});				 
			
function targetSet(onOff)
{
	var val = 0;
	for(var t=0; t<gData.s_data.m_channelCount; t++)
	{		
		if(onOff == 'on') val = gData.s_data.a_channelPwm[t];	
		else val = 0;	
		targetChannelUpdate(t,val);	
	}
}
		
var gRpcId = 0;
function targetChannelUpdate(channel, value)
{
	if(typeof channel === 'string') channel = parseInt(channel);
	if(typeof value === 'string') value = parseInt(value);
	
	var rpcRequest = new __pwmSetRequest(channel, value, gRpcId++);	
	rpcRequest = JSON.stringify(rpcRequest);
	
	$.ajax({
    // la URL para la petición
    url : gRpcUrl,
 
    // la información a enviar
    // (también es posible utilizar una cadena de datos)
    data : rpcRequest,
 
    // especifica si será una petición POST o GET
    type : 'POST',
 
    // el tipo de información que se espera de respuesta
    dataType : 'json',
 
    // código a ejecutar si la petición es satisfactoria;
    // la respuesta es pasada como argumento a la función
    success : function(json) {
        console.log('ajax success');
    },
 
    // código a ejecutar si la petición falla;
    // son pasados como argumentos a la función
    // el objeto de la petición en crudo y código de estatus de la petición
    error : function(xhr, status) {
        console.log('ajax error: ' + status);
    },
 
    // código a ejecutar sin importar si la petición falló o no
    complete : function(xhr, status) {
        console.log('ajax complete');
    }
});
}
			
function guiBuild()
{
	var html = "";
	//html = $(gSliderContainer).html();
	
	var t = 0;
	
	var template = "";
	for(t=0; t<gData.s_data.m_channelCount; t++)
	{
		var slider = "slider_Input_"+t;
		template = gSliderTemplate;
		template = template.replace("###slider_Input_Id###",slider);
		template = template.replace("###slider_Input_Id###",slider);
		template = template.replace("###slider_Channel###","Channel "+(t+1));
		template = template.replace("###slider_Value###",0);
		template = template.replace("###channel_number###", ""+t);
		
		html += template;
		
		$( document ).on( 'slidestop', '#'+slider, function( e, ui ) 
		{ 
			var cn = $(this).attr("channel-number");
			console.log("Channel " + cn + " , Value " + $(this).val());
			gData.s_data.a_channelPwm[cn] = $(this).val();
			targetChannelUpdate(cn, gData.s_data.a_channelPwm[cn]);
		});
	}	

	$(gSliderContainer).empty().append(html).enhanceWithin();	
}

function guiUpdate()
{
	var t = 0;
	for(t=0; t<gData.s_data.m_channelCount; t++)
	{	
		var slider = "slider_Input_"+t;
		$('#'+slider).val(gData.s_data.a_channelPwm[t]).slider("refresh");
	}
	
	$('#targetIp').val(gData.s_data.m_targetIp);
	$('#targetPort').val(gData.s_data.m_targetPort);
	$('#channelCount').val(gData.s_data.m_channelCount);
}

function guiEventsInit()
{
	$(document).on( 'change', '#flip-1', function( e ) 
	{
		console.log("Switch Value " + $(this).val());
		targetSet($(this).val());
	});

	$(document).on( 'change', '#targetIp', function( e ) 
	{
		gData.s_data.m_targetIp = $('#targetIp').val();
		console.log("targetIp change to "+gData.s_data.m_targetIp);
		gData.save(); 
		guiUpdate();
	});
	
	$(document).on( 'change', '#targetPort', function( e ) 
	{
		gData.s_data.m_targetPort = $('#targetPort').val();
		console.log("targetPort change to "+gData.s_data.m_targetPort);
		gData.save(); 
		guiUpdate();
	});
	
	$(document).on( 'change', '#channelCount', function( e ) 
	{
		gData.s_data.m_channelCount = $('#channelCount').val();
		console.log("channelCount change to "+gData.s_data.m_channelCount);
		gData.save(); 
		guiBuild();
		guiUpdate();
	});
}

