var oActiveX, oImgCaption;
var oSelectImg, oUpload, oFileName;
function init()
{
    oActiveX = document.getElementById( 'idResizer' );
    oImgCaption = document.getElementById( 'idImgCaption' );
    oSelectImg = document.getElementById( 'idSelectImg' );
    oUpload = document.getElementById( 'idUpload' );
    oFileName = document.getElementById( 'idFileName' );
    
    oImgCaption.innerText = oActiveX.ImagePropsDescription;
    
    oSelectImg.onclick = onSelect;
    oUpload.onclick = onUpload;
    oFileName.onkeydown = onKeyDownFile;
    
    oFileName.value = oActiveX.ImageFullName;
}

function onSelect()
{
//alert( oActiveX.DialogMasks );
    var fullName = oActiveX.SelectImage();
    if( fullName.length > 0 )
    {
        oFileName.value = fullName;
        oActiveX.ImageFullName = fullName;
        oImgCaption.innerText = oActiveX.ImagePropsDescription;
    }
}
function onUpload()
{    
	try
	{
		if( oActiveX.ImageFullName.length == 0 )
			alert( 'No image selected.' );
		else
			oActiveX.UploadImage();
    }
    catch( e )
    {
		alert( e.description );
    }
}
function onKeyDownFile()
{
    var e = window.event;    
    if( e.keyCode == 13 )
    {
        oActiveX.ImageFullName = oFileName.value;
        oImgCaption.innerText = oActiveX.ImagePropsDescription;
        return false;
    }
    else
        return true;
}


