var idtype;
//    CRMarcas = 0,
//    CRCategorias = 1,
//    CRMedidas= 2,
//    CRTipos = 3
function CallGenericos(genericoActive)
{
   idtype = genericoActive;
   ClearGenerica(1);
   $(ventana1).html(QT.GetTable(idtype));
   $(ventana1).dialog({
       autoOpen:true,
       height: 600,
       buttons:{
           Agregar: function(){
               ClearGenerica(2);
               $(ventana2).html(QT.GetForm(idtype,0));
                 $(ventana2).dialog({
                   autoOpen:true,
                   height: 600,                   
                   buttons:{
                     Agregar: function(){
                            if(JAgregarGenericos())
                            {
                                growcall('Catalogos','Agregado Correctamente');
                               $(this).dialog('close'); 
                               $(ventana1).html(QT.GetTable(idtype));
                            }
                    }
       }
   });
           }
       }
   });
}
//Qt.qt_to_js.connect(qt_to_js); 
//obj conector . nombre senal . connect(funcion java);

function JGetGenericosbyID(cod)
{
    ClearGenerica(2);
    $(ventana2).html(QT.GetForm(idtype, cod));
    $(ventana2).dialog({
        autoOpen: true,
        height: 600,
        buttons: {
            Agregar: function() {
                if (JAgregarGenericos())
                {
                    growcall('Catalogos', 'Modificado Correctamente');
                    $(this).dialog('close');
                    $(ventana1).html(QT.GetTable(idtype));
                }
            }
        }
    });
}

function JDeleteGenericosbyID(cod)
{
    if (QT.Borrar(idtype, cod))
    {
        $(ventana1).html(QT.GetTable(idtype));
        growcall('Catalogos', 'Borrado Correctamente');
    }
    else
        growcall('Catalogos', 'Error al borrar');
}

function JAgregarGenericos()
{
    if(!ValidateTXT($('#txt_Genericos_Nombre')))
        return false;
    if(!ValidateTXT($('#txt_Genericos_abre')))
        return false;
    if(!ValidateTXT($('#txt_Genericos_Descripcion')))
        return false;
    var request = {
                  'CodGenerico':$('#Cod_Generico').val(),
                  'Nombre':$('#txt_Genericos_Nombre').val(),
                  'Abre':$('#txt_Genericos_abre').val(),
                  'Descripcion':$('#txt_Genericos_Descripcion').val()
                  };
    if(!QT.Guardar(idtype,parseToString(request)))
        return false;
    return true;
} 
