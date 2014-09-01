var modalActive;
var marcaCod;
var proveedores;
function CallProductos()
{
    proveedores = [];
    marcaCod = -1;
    ClearGenerica(1);
    $(ventana1).html(QT.GetTable(6,0,parseToString({'action':0})));
    $(ventana1).dialog({
        autoOpen: true,
        height: 600,
        width:800,
        resizable: false, 
        title:'Producto',
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
    $(ventana2).html(QT.GetForm(6, cod));
    $('#cb_pro_medida').menu();
    $('#cb_pro_categoria').menu();
    $(ventana2).dialog({
        autoOpen: true,
        height: 660,
        width:700,
        resizable: false,
        title:'Productos',
        buttons: {
            Agregar: function() {
                if (GuardarProducto())
                {
                    growcall('Productos / Distribuidores', 'Agregado Correctamente');
                    $(this).dialog('close');
                    $(ventana1).html(QT.GetTable(6,0,parseToString({'action':0})));
                }
            }
        }
    });
    $('#txt_filtro').keyup(function(){
       $('#tb_util_destino').html(QT.GetTable(6,0,parseToString({'action':modalActive,'filter':$(this).val()})));
    });
}



function GuardarProducto()
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
    if(!QT.Guardar(6,parseToString(request)))
    {
        mensajebox(QT.GetError());
        return false;
    }
    return true;
}

function getProductoByID(cod)
{
    create_form(cod);
}

function DeleteProductoByID(cod)
{
    if(!QT.Borrar(6,cod))
    {
        alert(QT.GetError());
    }
    else
    {
         growcall('Productos / Distribuidores','Registro borrado correctamente')
         $(ventana1).html(QT.GetTable(6,0,parseToString({'action':0})));
    }
}

function ShowTableUtil(type)
{
    modalActive = type;
    $('#tb_util_destino').html(QT.GetTable(6,0,parseToString({'action':modalActive,'filter':""})));
    
    $('#tb_util').dialog({
        autoOpen: true,
        height: 600,
        width:800,
        resizable: false, 
        title:'Seleccione un elemento',
        buttons:{
            Cerrar: function(){
                $(this).dialog('close');
            }
        }
    });
    
}


function addProveedor(cod,name)
{
    $('#tb_util').dialog('close');
    var str = "<div id='"+cod+"' class='proveedorbox' ><span>"+name+"</span><input type='button' class='botoneliminar' style='float: right; margin-right: 10px;' ></div>";
    $('#frm_proveedores').append(str);
    $('#txt_filtro').val('');
}

function addMarca(cod,name)
{
    $('#txt_marcaSelecte').val(name);
    marcaCod = cod;
    $('#tb_util').dialog('close');
    $('#txt_filtro').val('');
}