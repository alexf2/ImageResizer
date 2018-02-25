<%@ Page language="c#" Codebehind="logon.aspx.cs" AutoEventWireup="false" Inherits="UploadTest.logon" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" >
<HTML>
	<HEAD>
		<title>logon</title>
		<meta content="Microsoft Visual Studio .NET 7.1" name="GENERATOR">
		<meta content="C#" name="CODE_LANGUAGE">
		<meta content="JavaScript" name="vs_defaultClientScript">
		<meta content="http://schemas.microsoft.com/intellisense/ie5" name="vs_targetSchema">
		<LINK href="css/Test.css" type="text/css" rel="stylesheet">
	</HEAD>
	<body MS_POSITIONING="GridLayout">
		<form id="Form1" method="post" runat="server">
			<table class="CLogon" height="100%" cellSpacing="0" cellPadding="0" width="100%" border="0">
				<tr>
					<td vAlign="middle" align="center">
						<div style="PADDING-RIGHT: 1em; PADDING-LEFT: 1em; PADDING-BOTTOM: 1em; PADDING-TOP: 1em"
							align="center">
							<table class="CLogon" style="BORDER-COLLAPSE: collapse" cellSpacing="0" cellPadding="0"
								border="0">
								<tr>
									<td align="right">Login name:</td>
									<td><input id="idLogin" style="width:10em" type="text" runat="server"><asp:Label id="isLblErrLogin" runat="server" Visible="false" ForeColor="Red" /></td>
								</tr>
								<tr>
									<td align="right">Password:</td>
									<td><input id="idPwd" style="width:10em" type="password" runat="server"></td>
								</tr>
								<tr>
									<td vAlign="middle" align="center" colSpan="2"><input id="idLogonBtn" type="button" value="Logon" runat="server"></td>
								</tr>
							</table>
						</div>
					</td>
				<tr>
				</tr>
			</table>
			<table>
		</form>
		</TABLE>
	</body>
</HTML>
