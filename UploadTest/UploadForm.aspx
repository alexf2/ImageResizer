<%@ Page language="c#" Codebehind="UploadForm.aspx.cs" AutoEventWireup="false" Inherits="UploadTest.UploadForm" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" >
<HTML>
	<HEAD>
		<title>WebForm1</title>
		<meta content="Microsoft Visual Studio .NET 7.1" name="GENERATOR">
		<meta content="C#" name="CODE_LANGUAGE">
		<meta content="JavaScript" name="vs_defaultClientScript">
		<meta content="http://schemas.microsoft.com/intellisense/ie5" name="vs_targetSchema">
	</HEAD>
	<body MS_POSITIONING="GridLayout">
		<form id="Form1" action="UploadForm.aspx" method="post" encType="multipart/form-data"
			runat="server">
			<input type="file" id="idFile" name="nFile"><br>
			<input type="submit" id="idSubm" name="nSubm" value="Upload">
			<asp:Button id="idBtnSignOut" runat="server" Text="SIgnOut" />
		</form>
	</body>
</HTML>
