function CallProveedores()
{
    ClearGenerica(1);
    $(ventana1).html(QT.GetTable(5));
    $(ventana1).dialog({
        autoOpen: true,
        height: 600,
        width:800,
        resizable: false, 
        title:'Proveedores',
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
    $(ventana2).html(QT.GetForm(5, cod));
    $('#cb_empresa').menu();
    $(ventana2).dialog({
        autoOpen: true,
        height: 660,
        width:700,
        resizable: false,
        title:'Proveedores',
        buttons: {
            Agregar: function() {
                if (GuardarProveedor())
                {
                    growcall('Productos / Distribuidores', 'Agregado Correctamente');
                    $(this).dialog('close');
                    $(ventana1).html(QT.GetTable(5));
                }
            }
        }
    });
}



function GuardarProveedor()
{
    if(!ValidateTXT($('#txt_persona_Nombre')))
        return false;
    if(!ValidateTXT($('#txt_persona_telefono1')))
        return false;
    if(!ValidateTXT($('#txt_persona_telefono2')))
        return false;
    if(!ValidateTXT($('#txt_persona_email')))
        return false;
    if(!ValidateTXT($('#txt_persona_cedula')))
        return false;
    if($('#cb_empresa option:selected').val() === '-1')
    {
        mensajebox("Seleccione una empresa");
        return false;
    }
    if(!ValidateTXT($('#txt_persona_direccion')))
        return false;

    var request = {'Cod_persona':$('#Cod_persona').val(), 'nombre':$('#txt_persona_Nombre').val(),'tel1':$('#txt_persona_telefono1').val(),
                   'tel2':$('#txt_persona_telefono2').val(),'email':$('#txt_persona_email').val(),
                   'cedula':$('#txt_persona_cedula').val(),'empre':$('#cb_empresa option:selected').val(),
                   'direccion':$('#txt_persona_direccion').val()};
    if(!QT.Guardar(5,parseToString(request)))
    {
        mensajebox(QT.GetError());
        return false;
    }
    return true;
}

function getProveedorByID(cod)
{
    create_form(cod);
}

function DeleteProveedorByID(cod)
{
    if(!QT.Borrar(5,cod))
    {
        alert(QT.GetError());
    }
    else
    {
         growcall('Productos / Distribuidores','Registro borrado correctamente')
         $(ventana1).html(QT.GetTable(5));
    }
}