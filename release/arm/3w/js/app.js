var gData = new appData();
var gRpcUrl = "json.rpc";

$(document).ready(function() {

    $("#menuContainerId").load("dyn.menu.html", function() {
        //OSLL: Default view is called...
        $("#dynMenuDefaultId").click();
    });

    dynInit("viewContainerId");
$('body').on('click', '.navbar-item a', function(e) { dynOnMenuClick(e);});


});

/*
function guiBuild() {
    var html = "";
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
*/
