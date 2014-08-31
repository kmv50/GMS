var ubicacion;
var map;
var marker;
function CallEmpresas()
{
    create_form(0);
    initialize();
       google.maps.event.addListener(marker, 'dragend', function(){
       ubicacion = marker.getPosition();
 }); 
     decirHola();
} 
function create_form(cod)
{
    ClearGenerica(2);
    $(ventana2).html(QT.GetForm(4, cod));
    $(ventana2).dialog({
        autoOpen: true,
        height: 700,
        width:1000,
        resizable: false,
        buttons: {
            Agregar: function() {
                if (JAgregarGenericos())
                {
                    growcall('Catalogos', 'Agregado Correctamente');
                    $(this).dialog('close');
                    $(ventana1).html(QT.GetTable(idtype));
                }
            }
        }
    });

}

function initialize() 
{
     
      geocoder = new google.maps.Geocoder();
        
      
         var latLng = new google.maps.LatLng(9.947777799999999,-84.05472220000001);
      
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