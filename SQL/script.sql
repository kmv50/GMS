#database GMS

create table TB_Empresas
(
Cod_empresa int not null AUTO_INCREMENT,
Nombre VARCHAR(50) not null,
Telefono varchar(20) not null,
Telefono2 varchar(20) not null,
Latitud decimal(17,15)  null,
Longitud decimal(17,15) null,
Direccion varchar(250) not null,
Email varchar(70) not null,
Pagina_Web varchar(250) not null,
Description text not null,#para que pege lo que le de la gana mision vision ...
Estado tinyint(1) not null,
constraint PK_Empresas primary key clustered
(
 Cod_empresa desc 
)
);


#puede ser un cliente o un vendedor 
create table TB_Personas
(
Cod_persona int not null AUTO_INCREMENT,
Nombre VARCHAR(50) not null,
Cedula int not null unique ,
Telefono varchar(20) not null,
Telefono2 varchar(20) null,
Email varchar(70) not null,
Direccion varchar(300) not null,
Estado tinyint(1) not null,
constraint PK_personas primary key clustered 
(
cod_persona desc
)
);


#esta no tiene estado xq lo hereda
CREATE TABLE TB_Proveedores
(
Id_personas int not null,
Id_empresa int not null,
constraint PK_proveedores primary key clustered
(
Id_personas desc , Id_empresa desc
)
);

alter table TB_Proveedores add constraint FK_proveedores_Personas_Cod_persona
foreign key(Id_personas) references TB_Personas (Cod_persona) on delete cascade;

alter table TB_Proveedores add constraint FK_proveedores_empresas_cod_empresa
foreign key(Id_empresa) references TB_Empresas (Cod_empresa) on delete cascade;


CREATE TABLE TB_Marcas(
Cod_marca int not null AUTO_INCREMENT,
Nombre VARCHAR(75) not null unique,
Descripcion VARCHAR(200) not null,
Abreviacion CHAR(10) not null unique,
Estado tinyint(1) not null,
constraint PK_Marcas primary key clustered
(
Cod_marca desc 
)
);

CREATE TABLE TB_Categorias(
Cod_categoria int not null AUTO_INCREMENT,
Nombre VARCHAR(75) not null unique,
Descripcion varchar(200) not null,
Abreviacion Char(10) not null unique,
Estado tinyint(1) not null,
constraint PK_Categorias primary key clustered
(
Cod_categoria desc
)
);

CREATE TABLE TB_Medidas
(
Cod_medida int not null AUTO_INCREMENT,
Nombre VARCHAR(75) not null unique,
Descripcion varchar(150) not null,
Abreviacion Char(10) not null unique,
Estado tinyint(1) not null,
constraint PK_Medidas primary key clustered
(
Cod_medida desc 
)
);

create table TB_Productos 
(
Cod_producto int not null AUTO_INCREMENT,
nombre varchar(50) not null unique,
Precio_compra decimal(10,2) not null,
Precio_venta decimal(10,2) not null,
Estado tinyint(1) not null,
Id_medida int not null,
Id_categoria int not null,
Id_marca int not null,
constraint PK_Productos primary key clustered
(
Cod_producto desc 
)
);

alter table TB_Productos add constraint FK_Productos_medidas_cod_medida 
foreign key(Id_medida) references TB_Medidas (Cod_medida);

alter table TB_Productos add constraint FK_Producto_Categoria_Cod_Categoria
foreign key(Id_categoria) references TB_Categorias (Cod_categoria);

alter table TB_Productos add constraint FK_Producto_Marcas_Cod_marca
foreign key(Id_marca) references TB_Marcas (Cod_marca);

create table TB_Productos_Proveedores
(
Id_producto int not null,
Id_proveedor int not null,
constraint PK_Productos_Proveedores primary key clustered
(
id_producto desc , id_proveedor desc
)
);

alter table TB_Productos_Proveedores add constraint FK_Productos_Proveedores_Producto_Cod_producto
foreign key(id_producto) references TB_Productos (Cod_producto);

alter table TB_Productos_Proveedores add constraint FK_Productos_Proveedores_Proveedor_Cod_proveedor
foreign key(id_proveedor) references TB_Proveedores (Id_personas);

CREATE TABLE TB_Tipos
(
Cod_tipo int not null AUTO_INCREMENT,
Nombre VARCHAR(75) not null unique,
Descripcion varchar(150) not null,
Abreviacion Char(10) not null unique,
Estado tinyint(1) not null,
constraint PK_MedidasTipos primary key clustered
(
Cod_tipo desc 
)
);

create table TB_Tipos_Productos 
(
Id_producto int not null,
Id_tipo int not null,
constraint PK_Tipos_Productos primary key clustered
(
id_producto desc , id_tipo desc
)
);

alter table TB_Tipos_Productos add constraint FK_TiposProductos_Productos_Cod_producto
foreign key(Id_producto) references TB_Productos (Cod_producto);

alter table TB_Tipos_Productos add constraint FK_TiposProductos_Tipos_Cod_Tipo
foreign key(Id_tipo) references TB_Tipos (Cod_tipo);

create table TB_Inventarios
(
Cod_inventario bigint not null AUTO_INCREMENT,
Cantidad int not null, 
Fecha datetime not null,
Id_producto int not null,
Id_proveedor int not null,
constraint PK_Inventarios primary key clustered
(
Cod_inventario desc 
)
);

alter table TB_Inventarios add constraint FK_Inventarios_Productos_Cod_producto
foreign key(Id_producto) references TB_Productos (Cod_producto);

alter table TB_Inventarios add constraint FK_Inventarios_Proveedores_Cod_proveedor
foreign key(Id_proveedor) references TB_Proveedores (Id_personas);

create table TB_Facturas
(
Cod_factura bigint not null AUTO_INCREMENT,
Total decimal(10,2) not null,
Fecha datetime not null,
Id_cliente int not null,
constraint PK_Facturas primary key clustered
(
Cod_factura desc 
)
);

alter table TB_Facturas add constraint FK_Facturas_Personas_Cod_persona
foreign key(Id_cliente) references TB_Personas (Cod_persona);

create table TB_Facturas_producto
(
Cantidad int not null,
PrecioUnitarioOriginal decimal(8,2) not null,#lo pongo asi y no me lo traigo con inner xq el precio de la factura no se debe variar 
Id_producto int not null,
Id_Factura bigint not null,
constraint PK_Facturas_producto primary key clustered
(
 Id_producto desc , Id_Factura desc
)
);

alter table TB_Facturas_producto add constraint FK_FacturasProducto_Facturas_Cod_factura
foreign key (Id_Factura) references TB_Facturas (Cod_factura);

alter table TB_Facturas_producto add constraint FK_FacturasProducto_Productos_Cod_producto
foreign key (Id_producto) references TB_Productos (Cod_producto);


delimiter $$

create procedure sp_setGenerico
(
Action tinyint(1),
_Cod_Generico int,
_Nombre varchar(75),
_Descripcion varchar(200),
_Abreviacion char(10)
)
begin
#marcas
if(Action = 0)then
   if(_Cod_Generico = 0)then
      insert into TB_Marcas values(null,_Nombre,_Descripcion,_Abreviacion,1);
   else
      update TB_Marcas set Nombre = _Nombre ,Descripcion = _Descripcion ,Abreviacion = _Abreviacion where Cod_marca = _Cod_Generico;
   end if;
end if;
#Cagorias
if(Action = 1)then
   if(_Cod_Generico = 0)then 
      insert into TB_Categorias values(null,_Nombre,_Descripcion,_Abreviacion,1);
   else 
      update TB_Categorias set Nombre = _Nombre, Descripcion = _Descripcion , Abreviacion = _Abreviacion where Cod_categoria = _Cod_Generico;
   end if;
end if;
#medidas
if(Action = 2)then
   if(_Cod_Generico = 0)then 
      insert into TB_Medidas values(null,_Nombre,_Descripcion,_Abreviacion,1);
   else 
      update TB_Medidas set Nombre = _Nombre, Descripcion = _Descripcion , Abreviacion = _Abreviacion where Cod_medida = _Cod_Generico;
   end if;
end if;
#Tipos
if(Action = 3)then
   if(_Cod_Generico = 0)then 
      insert into TB_Tipos values(null,_Nombre,_Descripcion,_Abreviacion,1);
   else 
      update TB_Tipos set Nombre = _Nombre, Descripcion = _Descripcion , Abreviacion = _Abreviacion where Cod_tipo = _Cod_Generico;
   end if;
end if;
end;$$

create procedure sp_getGenerico
(
Action tinyint(1),
_Cod_Generico int
)
begin 
#marcas
if(Action = 0)then
     if(_Cod_Generico = 0)then
       select Cod_marca , Nombre , Abreviacion from TB_Marcas where Estado = 1;
     else
       select Nombre , Descripcion , Abreviacion from TB_Marcas where Cod_marca = _Cod_Generico;
     end if;
end if;
#Cagorias
if(Action = 1)then
   if(_Cod_Generico = 0)then
      select Cod_categoria , Nombre , Abreviacion from TB_Categorias where Estado = 1;
   else 
      select Nombre , Descripcion , Abreviacion  from TB_Categorias where Cod_categoria = _Cod_Generico;
   end if;
end if;
#MEdidas
if(Action = 2)then
   if(_Cod_Generico = 0)then
      select Cod_medida , Nombre , Abreviacion from TB_Medidas where Estado = 1;
   else 
      select Nombre , Descripcion , Abreviacion  from TB_Medidas where Cod_medida = _Cod_Generico;
   end if;
end if;
#tipos
if(Action = 3)then
   if(_Cod_Generico = 0)then
      select Cod_tipo , Nombre , Abreviacion from TB_Tipos where Estado = 1;
   else 
      select Nombre , Descripcion , Abreviacion  from TB_Tipos where Cod_tipo = _Cod_Generico;
   end if;
end if;
end;$$


create procedure sp_deleteGenerico
(
Action tinyint(1),
cod int
)
begin
#marcas
if(Action = 0)then
  if(exists(select Id_marca from TB_Productos where Id_marca = cod))then
     update TB_Marcas set Estado = 0 where Cod_marca = cod;
  else
     delete from TB_Marcas where Cod_marca = cod;
  end if;
end if;
#Cagorias
if(Action = 1)then
  if(exists(select Id_categoria from TB_Productos where Id_categoria = cod))then
     update TB_Categorias set Estado = 0 where Cod_categoria = cod;
  else
     delete from TB_Categorias where Cod_categoria = cod;
  end if;
end if;
#medidas
if(Action = 2)then
  if(exists(select Id_medida from TB_Productos where Id_medida = cod))then
     update TB_Medidas set Estado = 0 where Cod_medida = cod;
  else
     delete from TB_Medidas where Cod_medida = cod;
  end if;
end if;
#tipo
if(Action = 2)then
  if(exists(select Id_tipo from TB_Tipos_Productos where Id_tipo = cod))then
     update TB_Tipos set Estado = 0 where Cod_tipo = cod;
  else
     delete from TB_Tipos where Cod_tipo = cod;
  end if;
end if;
end;$$
#no creado
create procedure sp_setProductos
(
_Cod_producto   int(11),       
_nombre         varchar(50),   
_Precio_compra  decimal(10,2), 
_Precio_venta   decimal(10,2),
_Id_medida      int(11),   
_Id_categoria   int(11),      
_Id_marca       int(11)
)
begin 
  if(_Cod_producto = 0)then 
     insert into TB_Productos values (null,_nombre,_Precio_compra,_Precio_venta,1,_Id_medida,_Id_categoria,_Id_marca);
     select Cod_producto from TB_Productos order by Cod_producto desc limit 1;
  else 
     update TB_Productos set nombre= _nombre,Precio_compra = _Precio_compra ,Precio_venta = _Precio_venta,
     Id_medida = _Id_medida, Id_categoria = _Id_categoria ,Id_marca = _Id_marca where Cod_producto = _Cod_producto;
  end if;
end;$$
#no creado
create procedure sp_getProductos 
(
_Cod_producto int
)
begin 
   if(_Cod_producto = 0)then 
      select Cod_producto , nombre , Precio_compra , Precio_venta from TB_Productos  where Estado = 1;
   else 
      select pro.nombre , Precio_compra , Precio_venta , Id_medida , Id_categoria , Id_marca , mar.nombre from TB_Productos as pro
      inner join TB_Marcas as mar on Id_marca = Cod_marca where Cod_producto = _Cod_producto;
   end if;
end;$$

create procedure sp_setEmpresas
(
_Cod_empresa int,
_nombre varchar(50),
_telefono varchar(20),
_telefono2 varchar(20),
_latitud decimal(17,15),
_longitud decimal(17,15),
_Direccion varchar(250),
_email varchar(70),
_web varchar(250),
_Descripcion text
)
begin
   if(_Cod_empresa = 0)then
      insert into TB_Empresas values(null,_nombre,_telefono,_telefono2,_latitud,_longitud,_Direccion,_email,_web,_Descripcion,1);
   else 
      update TB_Empresas set Nombre = _nombre,Telefono = _telefono,Telefono2 = _telefono2,
      Latitud = _latitud,Longitud = _longitud,Direccion = _Direccion,Email = _email,Pagina_Web = _web,Description = _Descripcion where Cod_empresa = _Cod_empresa;
   end if;
end;$$


create procedure sp_getEmpresas 
(
_Cod_Empresa int 
)
begin 
   if(_Cod_Empresa = 0)then
      select Cod_empresa , Nombre , Telefono , Email from TB_Empresas where  Estado = 1;
   else 
      select Nombre , Telefono , Telefono2 , Latitud , Longitud , Direccion , Email,
      Pagina_Web , Description from TB_Empresas  where Cod_empresa = _Cod_Empresa;
   end if;
end;$$

create procedure sp_getCbEmpresas()
begin 
  select Cod_empresa , nombre from TB_Empresas;
end;$$

create procedure sp_getProveedor
(
_Cod_proveedor int 
)
begin 
   if(_Cod_proveedor = 0)then 
      select Cod_persona , per.Nombre , per.Telefono ,empre.Nombre  from TB_Proveedores
      inner join TB_Personas as per on Id_personas = Cod_persona 
      inner join TB_Empresas as empre on Id_empresa = Cod_empresa
      where per.Estado = 1 and empre.Estado = 1;
   else 
      select Nombre , Cedula , Telefono , Telefono2 , Direccion,Email  ,Id_empresa from TB_Proveedores
      inner join TB_Personas on Id_personas = Cod_persona 
      where Cod_persona = _Cod_proveedor;
   end if;
end;$$

create procedure sp_setProveedores
(
_Cod_persona int ,
_nombre varchar(50),
_Cedula int,
_telefono varchar(20),
_telefono2 varchar(20),
_Email varchar(70),
_Direccion varchar(300),
_Id_empresa int 
)
begin 
   
   declare codPersonaLst int;
   
   if(_Cod_persona = 0)then 
      insert into TB_Personas values(null,_nombre,_Cedula,_telefono,_telefono2,_Email,_Direccion,1);
      set codPersonaLst = (select Cod_persona from TB_Personas order by Cod_persona desc limit 1);
      insert into TB_Proveedores values(codPersonaLst , _Id_empresa);
   else 
      update TB_Personas set Nombre = _nombre , Cedula = _Cedula , Telefono = _telefono , Telefono2 = _telefono2,
      Email = _Email , Direccion = _Direccion where Cod_persona = _Cod_persona;
      update TB_Proveedores set Id_empresa = _Id_empresa where Id_personas = _Cod_persona;
   end if;
end;$$


