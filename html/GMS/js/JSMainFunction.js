var positionMainFrame = 0;
var ventana1 = "#VentanaGenerica1";
var ventana2 = "#VentanaGenerica2";
$(document).ready(function(){
    //BackGroudChange();
    growcall('GMS','Bienvenido');
    ClearGenerica(1);
    ClearGenerica(2);
    positionMainFrame -= 1200;
    $('#DialogBox').dialog({
       modal:true,
       autoOpen:false,
       position:'top',
       width:500,
       height: 350,
       resizable: false,
       buttons:{
           Cerrar: function(){$(this).dialog('close');}
       }
    });
    $('#mainContenedor').css({"-webkit-transform": "translate(" + positionMainFrame + "px)"});
        $('body').animate({
            'background-position-x': positionMainFrame+'px'
     }, 1000, 'linear');
        
    $('#rightBar').click(function() {
        positionMainFrame -= 1000;
        $('#mainContenedor').css({"-webkit-transform": "translate(" + positionMainFrame + "px)"});
        $('body').animate({
            'background-position-x': positionMainFrame+'px'
        }, 1000, 'linear');
        if(positionMainFrame === -1200)
        {
            $('#tb_inventarios').html(QT.GetTable(0));
        }
    }); 
    $('#leftBar').click(function() {
        positionMainFrame += 1000;
        $('#mainContenedor').css({"-webkit-transform": "translate(" + positionMainFrame + "px)"});
        $('body').animate({
            'background-position-x': positionMainFrame + 'px'
        }, 1000, 'linear');
        if(positionMainFrame === -1200)
        {
            $('#tb_inventarios').html(QT.GetTable(0));
        }
    }); 
   // $('#tb_inventarios').html(QT.GetTable(0));
});

function parseToString(Json)
{
    return JSON.stringify(Json);
}


function  bloquear(mensaje)
{
    if(mensaje === -1)
    {
      $('#lb_bloqMensaje').html('Espere por favor');  
    }
    else
    {
    $('#lb_bloqMensaje').html(mensaje);
    }
       $.blockUI({ 
        message: $('#loaderDisplay'),
        css: { 
            border: 'none', 
            padding: '15px', 
            backgroundColor: '#000', 
            '-webkit-border-radius': '10px', 
            '-moz-border-radius': '10px', 
            opacity: .5, 
            color: '#fff' 
        } });    
}
function desbloquear()
{
    setTimeout($.unblockUI, 1);
}

function ClearGenerica(num)
{
     $('#VentanaGenerica'+num).html("");
    $('#VentanaGenerica'+num).dialog({
        position:'top',
        modal:true,
        autoOpen:false,
        width:600,
        height: 400,
        buttons:{
            Cerrar: function(){
                $(this).dialog('close');
            }    
         }
    });
}
function ValidateTXT(obj)
{
    if(obj.val() === "")
    {
        mensajebox("Campo incompleto o nulo");
        obj.focus();
        return false;
    }
    return true;
}
 function mensajebox(msn)
 {
        $('#lbl_msn').html(msn);
        $('#DialogBox').dialog('open');
 }
function growcall(titulo,mensaje)
{
   $(document).ready(function() { 
   $.growlUI(titulo, mensaje); //modificado en linea 159 
   });
}
var fondoActual = 0;
function BackGroudChange()
{
   var timeout = setTimeout(function(){
       console.log('http://gms123.esy.es/GMS/Fondos/'+fondoActual+'.png');
        $('body').css({'background-image':'url(http://gms123.esy.es/GMS/Fondos/'+fondoActual+'.png)'});
        fondoActual++;
        if(fondoActual > 5)
            fondoActual = 0;
        clearInterval(timeout);
        BackGroudChange();
    }, 10000);
   //clearTimeout(timeout);
}

