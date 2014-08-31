function loadScript(id)
{
    var head = document.getElementsByTagName('head').item(0);
    var script = document.createElement('script');
    script.setAttribute('id','SC_Generico');
    var strScript = QT.GetScript(id);
    script.text = strScript;
    head.appendChild(script);
}
function RemoveScript()
{
        $('#SC_Generico').remove();
}
function Create_Genericos(id)
{
    RemoveScript();
    loadScript(0);
    CallGenericos(id);
}
function Create_Empresa()
{
     RemoveScript();
    loadScript(4);
    CallEmpresas(0);
}