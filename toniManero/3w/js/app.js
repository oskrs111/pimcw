var gFlipState = 0;
$( document ).on( 'change', '#gk-95S2XR', function( e ) 
{
   if(gFlipState == 0) gFlipState = 1;
   else gFlipState = 0;
    
});

$( document ).on( 'slidestop', '#gk-95ycRH', function( e, ui ) 
{ 
    console.log($('#gk-95ycRH').val());
});

