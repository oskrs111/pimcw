var gData = new appData();
var gRpcUrl = "json.rpc";
var gSliderContainer = "#sliderContainer";
var gSliderTemplate = '<div class="ui-field-contain">';
gSliderTemplate += '<label for="###slider_Input_Id###">###slider_Channel###</label>';
gSliderTemplate += '<input id="###slider_Input_Id###" name="slider" class="custom-slider" channel-number="###channel_number###" value="###slider_Value###" min="0" max="100" type="range" data-highlight="true">';
gSliderTemplate += '</div>';

$(document).ready(function() {
    /*
    if (gData.checkConfig()) {
        gData.load();
    } else {
        gData.save();
    }

    guiBuild();
    guiUpdate();
    guiEventsInit();

       
       if(gData.checkDefault())
       {
    	   $( "#settingsPannel" ).trigger( "expand" );							
       }
    */
    gCurrentButton = null;
    setInterval(OnButtonTimer, 50);
    eventBind();

    $('.button-frame').each(function(index, value) {
        updateButton(index + '');
    });


    remoteChannelGetAll(getChannelCallback);
    setInterval(function() {
        remoteChannelGetAll(getChannelCallback);
    }, 1000);

});

function eventBind() {
    $('body').on('mousedown touchstart', '.function-increase', function(e) { OnIncrease(e); });
    $('body').on('mousedown touchstart', '.function-decrease', function(e) { OnDecrease(e); });
    $('body').on('mouseup touchend', '.function-increase', function(e) { OnIncrease(e); });
    $('body').on('mouseup touchend', '.function-decrease', function(e) { OnDecrease(e); });
    $('body').on('click', '.function-toggle', function(e) { OnToggle(e); });
}

var gCurrentChannel = null;
var gButtonState = 'sIdle';

function OnIncrease(event) {

    event.stopPropagation();
    switch (event.type) {
        case 'mousedown':
            gCurrentChannel = $(event.target).attr('tChnannelId');
            gButtonState = 'sIncrease';
            break;

        case 'mouseup':
        default:
            gButtonState = 'sIdle';
            gCurrentChannel = null;
            break;

    }

}

function OnDecrease(event) {

    event.stopPropagation();
    switch (event.type) {
        case 'mousedown':
            gCurrentChannel = $(event.target).attr('tChnannelId');
            gButtonState = 'sDecrease';
            break;

        case 'mouseup':
        default:
            gButtonState = 'sIdle';
            gCurrentChannel = null;
            break;

    }
}

function OnToggle(event) {

    var channelId = $(event.target).attr('tChnannelId');
    if (getButtonValue(channelId) === 0) {
        setButtonValue(channelId, getButtonValueBackup(channelId));
        remoteChannelSet(channelId, getButtonValue(channelId));
    } else {
        setButtonValueBackup(channelId, getButtonValue(channelId));
        setButtonValue(channelId, 0);
        remoteChannelSet(channelId, 0);
    }
    updateButton(channelId);
}

function OnButtonTimer() {

    if (gCurrentChannel === null) return;

    switch (gButtonState) {
        case 'sIdle':
            break;

        case 'sDecrease':
            decreaseChannelValue(gCurrentChannel);
            updateButton(gCurrentChannel);
            break;

        case 'sIncrease':
            increaseChannelValue(gCurrentChannel);
            updateButton(gCurrentChannel);
            break;

        default:
            break;
    }

}

function updateButton(channelId) {
    var value = getButtonValue(channelId);
    var root = $('#tChannel' + channelId);
    var text = root.find(".function-toggle p");
    if (value == 255) { //OSLL: Default state, need to get values from device...
        text[1].innerHTML = "...";
        root.addClass("button-frame-UNKNOWN");
    } else if (value > 0) {
        text[1].innerHTML = "ON";
        root.removeClass("button-frame-OFF");
        root.removeClass("button-frame-UNKNOWN");
        root.find(".button-path-text").removeClass("button-path-text-OFF");
        root.find(".button-svg").removeClass("button-svg-OFF");
        arcDraw(channelId, value);
    } else {
        text[1].innerHTML = "OFF";
        root.removeClass("button-frame-UNKNOWN");
        root.addClass("button-frame-OFF");
        root.find(".button-path-text").addClass("button-path-text-OFF");
        root.find(".button-svg").addClass("button-svg-OFF");
        arcDraw(channelId, value);
    }
}

function increaseChannelValue(channelId) {
    var value = getButtonValue(channelId);
    if (value < 100) {
        value++;
        setButtonValue(channelId, value);
        remoteChannelSet(channelId, value);
    }
}

function decreaseChannelValue(channelId) {
    var value = getButtonValue(channelId);
    if (value > 1) {
        value--;
        setButtonValue(channelId, value);
        remoteChannelSet(channelId, value);
    }
}

function getButtonValue(channelId) {
    var value = $('#tChannel' + channelId).attr('tChannelValue');
    return parseInt(value);
}

function setButtonValue(channelId, value) {
    $('#tChannel' + channelId).attr('tChannelValue', value);
}

function getButtonValueBackup(channelId) {
    var value = $('#tChannel' + channelId).attr('tChannelBackupValue');
    return parseInt(value);
}

function setButtonValueBackup(channelId, value) {
    $('#tChannel' + channelId).attr('tChannelBackupValue', value);
}

function arcDraw(itemIndex, value) {

    if (value > 100) value = 100;
    if (value < 0) value = 0;

    var svg = $("#tSvg" + itemIndex);
    var x = svg.width() / 2;
    var y = svg.height() / 2;
    var r = svg.width() / 3.5;
    var a = (360.0 / 100.0) * value;
    var text = $("#tText" + itemIndex);
    text.attr("x", x);
    text.attr("y", y);
    text[0].innerHTML = value.toFixed(0) + "%";
    $("#tArc" + itemIndex)[0].setAttribute("d", describeArc(x, y, r, 0, a - 1));
}

//http://jsbin.com/cibicecuto/edit?html,js,output

function polarToCartesian(centerX, centerY, radius, angleInDegrees) {
    var angleInRadians = (angleInDegrees - 90) * Math.PI / 180.0;

    return {
        x: centerX + (radius * Math.cos(angleInRadians)),
        y: centerY + (radius * Math.sin(angleInRadians))
    };
}

function describeArc(x, y, radius, startAngle, endAngle) {

    var start = polarToCartesian(x, y, radius, endAngle);
    var end = polarToCartesian(x, y, radius, startAngle);

    var arcSweep = endAngle - startAngle <= 180 ? "0" : "1";

    var d = [
        "M", start.x, start.y,
        "A", radius, radius, 0, arcSweep, 0, end.x, end.y
    ].join(" ");

    return d;
}
/*----------------------------------------------------------------------------------------------------------------*/
function getChannelCallback(reply) {

    if (reply.result.hasOwnProperty("duttyArray")) {
        for (var channelId = 0; channelId < reply.result.duttyArray.length; channelId++) {
            setButtonValue(channelId, reply.result.duttyArray[channelId]);
            updateButton(channelId);
        }
    }
}

function getAllChannelCallback(reply) {

}
/*----------------------------------------------------------------------------------------------------------------*/

__pwmSetRequest = function(channel, dutty, id)
    //{"jsonrpc": "2.0", "method": "pwmSet", "params": {"channel": 23, "dutty": 42}, "id": 4}
    {
        this.jsonrpc = "2.0";
        this.method = "pwmSet";
        this.params = { "channel": 0, "dutty": 0 };
        this.id = id;

        this.params.channel = channel;
        this.params.dutty = dutty;
    }

__pca9685SetRequest = function(channel, dutty, id)
    //{"jsonrpc": "2.0", "method": "pca9685Set", "params": {"channel": 23, "dutty": 42}, "id": 4}
    {
        this.jsonrpc = "2.0";
        this.method = "pca9685Set";
        this.params = { "channel": 0, "dutty": 0 };
        this.id = id;
        this.params.channel = channel;
        this.params.dutty = dutty;
    }

__pca9685GetRequest = function(channel, dutty, id)
    //{"jsonrpc": "2.0", "method": "pca9685Get", "params": {"channel": 23}, "id": 4}
    {
        this.jsonrpc = "2.0";
        this.method = "pca9685Get";
        this.params = { "channel": 0, "dutty": 0 };
        this.id = id;

        this.params.channel = channel;
        this.params.dutty = dutty;
    }

__pca9685GetAllRequest = function(id)
    //{"jsonrpc": "2.0", "method": "pca9685GetAll", "id": 4}
    {
        this.jsonrpc = "2.0";
        this.method = "pca9685GetAll";
        this.id = id;
    }

var gRpcId = 0;

function remoteChannelSet(channel, value) {
    if (typeof channel === 'string') channel = parseInt(channel);
    if (typeof value === 'string') value = parseInt(value);

    //var rpcRequest = new __pwmSetRequest(channel, value, gRpcId++);
    var rpcRequest = new __pca9685SetRequest(channel, value, gRpcId++);
    rpcRequest = JSON.stringify(rpcRequest);

    $.ajax({
        // la URL para la petición
        url: gRpcUrl,

        // la información a enviar
        // (también es posible utilizar una cadena de datos)
        data: rpcRequest,

        // especifica si será una petición POST o GET
        type: 'POST',

        // el tipo de información que se espera de respuesta
        dataType: 'json',

        // código a ejecutar si la petición es satisfactoria;
        // la respuesta es pasada como argumento a la función
        success: function(json) {
            console.log('ajax success');
        },

        // código a ejecutar si la petición falla;
        // son pasados como argumentos a la función
        // el objeto de la petición en crudo y código de estatus de la petición
        error: function(xhr, status) {
            console.log('ajax error: ' + status);
        },

        // código a ejecutar sin importar si la petición falló o no
        complete: function(xhr, status) {
            console.log('ajax complete');
        }
    });
}

function remoteChannelGet(channel, value, callback) {
    if (typeof channel === 'string') channel = parseInt(channel);
    if (typeof value === 'string') value = parseInt(value);

    var rpcRequest = new __pca9685GetRequest(channel, value, gRpcId++);
    rpcRequest = JSON.stringify(rpcRequest);

    $.ajax({
        // la URL para la petición
        url: gRpcUrl,

        // la información a enviar
        // (también es posible utilizar una cadena de datos)
        data: rpcRequest,

        // especifica si será una petición POST o GET
        type: 'POST',

        // el tipo de información que se espera de respuesta
        dataType: 'json',

        // código a ejecutar si la petición es satisfactoria;
        // la respuesta es pasada como argumento a la función
        success: function(json) {
            callback(json);
            console.log('ajax success');
        },

        // código a ejecutar si la petición falla;
        // son pasados como argumentos a la función
        // el objeto de la petición en crudo y código de estatus de la petición
        error: function(xhr, status) {
            console.log('ajax error: ' + status);
        },

        // código a ejecutar sin importar si la petición falló o no
        complete: function(xhr, status) {
            console.log('ajax complete');
        }
    });
}

function remoteChannelGetAll(callback) {
    if (typeof channel === 'string') channel = parseInt(channel);
    if (typeof value === 'string') value = parseInt(value);

    var rpcRequest = new __pca9685GetAllRequest(gRpcId++);
    rpcRequest = JSON.stringify(rpcRequest);

    $.ajax({
        // la URL para la petición
        url: gRpcUrl,

        // la información a enviar
        // (también es posible utilizar una cadena de datos)
        data: rpcRequest,

        // especifica si será una petición POST o GET
        type: 'POST',

        // el tipo de información que se espera de respuesta
        dataType: 'json',

        // código a ejecutar si la petición es satisfactoria;
        // la respuesta es pasada como argumento a la función
        success: function(json) {
            callback(json);
            console.log('ajax success');
        },

        // código a ejecutar si la petición falla;
        // son pasados como argumentos a la función
        // el objeto de la petición en crudo y código de estatus de la petición
        error: function(xhr, status) {
            console.log('ajax error: ' + status);
        },

        // código a ejecutar sin importar si la petición falló o no
        complete: function(xhr, status) {
            console.log('ajax complete');
        }
    });
}


function guiBuild() {
    var html = "";
    //html = $(gSliderContainer).html();

    var t = 0;

    var template = "";
    for (t = 0; t < gData.s_data.m_channelCount; t++) {
        var slider = "slider_Input_" + t;
        template = gSliderTemplate;
        template = template.replace("###slider_Input_Id###", slider);
        template = template.replace("###slider_Input_Id###", slider);
        template = template.replace("###slider_Channel###", "Channel " + (t + 1));
        template = template.replace("###slider_Value###", 0);
        template = template.replace("###channel_number###", "" + t);

        html += template;

        $(document).on('slidestop', '#' + slider, function(e, ui) {
            var cn = $(this).attr("channel-number");
            console.log("Channel " + cn + " , Value " + $(this).val());
            gData.s_data.a_channelPwm[cn] = $(this).val();
            targetChannelUpdate(cn, gData.s_data.a_channelPwm[cn]);
        });
    }

    $(gSliderContainer).empty().append(html).enhanceWithin();
}