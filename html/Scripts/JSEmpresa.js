var ubicacion;
var map;
var marker;
var latLng;

function CallEmpresas()
{
    ClearGenerica(1);
    $(ventana1).html(QT.GetTable(4));
    $(ventana1).dialog({
        autoOpen: true,
        height: 600,
        width:800,
        resizable: false, 
        title:'Empresas',
        buttons:{
            Agregar: function(){
                create_form(0);
            }
        }
    });
} 
function create_form(cod)
{
    ClearGenerica(2);
    var json = JSON.parse(QT.GetForm(4, cod));
    if(cod !== 0)
      latLng = new google.maps.LatLng(json['latitud'],json['longitud']);
    else
      latLng = new google.maps.LatLng(9.947777799999999,-84.05472220000001);
    
    $(ventana2).html(json['html']);
    $(ventana2).dialog({
        autoOpen: true,
        height: 700,
        width:1000,
        resizable: false,
        title:'Empresas',
        buttons: {
            Agregar: function() {
                if (GuardarEmpresa())
                {
                    growcall('Productos / Distribuidores', 'Agregado Correctamente');
                    $(this).dialog('close');
                    $(ventana1).html(QT.GetTable(4));
                }
            }
        }
    });
        initialize();
       google.maps.event.addListener(marker, 'dragend', function(){
       ubicacion = marker.getPosition();
       }); 
}

function initialize() 
{
     
      geocoder = new google.maps.Geocoder();
        
      
         
      
      //Definimos algunas opciones del mapa a crear
       var myOptions = {
          center: latLng,//centro del mapa
          zoom: 15,//zoom del mapa
          mapTypeId: google.maps.MapTypeId.ROADMAP //tipo de mapa, carretera, híbrido,etc
        };
        //creamos el mapa con las opciones anteriores y le pasamos el elemento div
        map = new google.maps.Map(document.getElementById("g_map"), myOptions);
         
        //creamos el marcador en el mapa
        marker = new google.maps.Marker({
            map: map,//el mapa creado en el paso anterior
            position: latLng,//objeto con latitud y longitud
            draggable: true //que el marcador se pueda arrastrar
        });
        
       //función que actualiza los input del formulario con las nuevas latitudes
       //Estos campos suelen ser hidden
       ubicacion = latLng;       
} 

function GuardarEmpresa()
{
    if(!ValidateTXT($('#txt_Genericos_Nombre')))
        return false;
    if(!ValidateTXT($('#txt_empre_telefono1')))
        return false;
    if(!ValidateTXT($('#txt_empre_telefono2')))
        return false;
    if(!ValidateTXT($('#txt_empre_email')))
        return false;
    if(!ValidateTXT($('#txt_empre_web')))
        return false;
    if(!ValidateTXT($('#txt_empre_descripcion')))
        return false;
    if(!ValidateTXT($('#txt_empre_direccion')))
        return false;
    if(ubicacion === null)
    {
          mensajebox("Seleccione una ubicacion en el mapa");
          return false;
    }

    var request = {'Cod':$('#Cod_empresa').val(),'Nombre':$('#txt_Genericos_Nombre').val(),'Tel1':$('#txt_empre_telefono1').val(),'Tel2':$('#txt_empre_telefono2').val(),
                   'email':$('#txt_empre_email').val(),'web':$('#txt_empre_web').val(),'description':$('#txt_empre_descripcion').val(),
                   'direccion':$('#txt_empre_direccion').val(),'latitud':ubicacion.lat(),'longitud':ubicacion.lng()};
    if(!QT.Guardar(4,parseToString(request)))
    {
        mensajebox(QT.GetError());
        return false;
    }
    return true;
}

function getEmpresaByID(cod)
{
    create_form(cod);
}

function DeleteEmpresaByID(cod)
{
    if(!QT.Borrar(4,cod))
    {
        alert(QT.GetError());
    }
    else
    {
         growcall('Productos / Distribuidores','Registro borrado correctamente')
         $(ventana1).html(QT.GetTable(4));
    }
}