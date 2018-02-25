using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Xml;
using System.IO;
using System.Text;
using System.Xml.Serialization;
using System.Drawing;
using System.Web;
using System.Web.SessionState;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;
using System.Diagnostics;
using System.Web.Security;

namespace UploadTest
{
	/// <summary>
	/// Summary description for logon.
	/// </summary>
	public class logon : System.Web.UI.Page
	{
		protected System.Web.UI.HtmlControls.HtmlInputText idLogin;
		protected System.Web.UI.HtmlControls.HtmlInputText idPwd;
		protected System.Web.UI.WebControls.Label isLblErrLogin;
		protected System.Web.UI.HtmlControls.HtmlInputButton idLogonBtn;

		private void Page_Load(object sender, System.EventArgs e)
		{
			/*RolesSection rs = new RolesSection();
			rs.Users = new UserItem[ 2 ];
			rs.Users[0] = new UserItem(); rs.Users[0].Name = "tt1"; rs.Users[0].Roles = "1|2|3";
			rs.Users[1] = new UserItem(); rs.Users[1].Name = "tt2"; rs.Users[1].Roles = "1|3";
			XmlSerializer s = new XmlSerializer( typeof(RolesSection) );
			StringBuilder sb = new StringBuilder();
			s.Serialize( new XmlTextWriter(new StringWriter(sb)), rs );
			String res = sb.ToString();
			Debugger.Log( 0, "", res );*/

			if( !IsPostBack )
			{
				HttpCookie cLog = Request.Cookies[ "LoginCook" ];
				HttpCookie cPass = Request.Cookies[ "PassCook" ];
				if( cLog != null )
					idLogin.Value = cLog.Value;
				if( cPass != null )
					idPwd.Value = cPass.Value;
			}
		}

		#region Web Form Designer generated code
		override protected void OnInit(EventArgs e)
		{
			//
			// CODEGEN: This call is required by the ASP.NET Web Form Designer.
			//
			InitializeComponent();
			base.OnInit(e);
		}
		
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{    
			this.idLogonBtn.ServerClick += new System.EventHandler(this.idLogonBtn_ServerClick);
			this.Load += new System.EventHandler(this.Page_Load);

		}
		#endregion

		private void idLogonBtn_ServerClick( object sender, System.EventArgs e )
		{
			FormsAuthentication.Initialize();

			Object passCnt = Session[ "LOGIN_COUNT" ];
			if( passCnt == null )
				Session[ "LOGIN_COUNT" ] = 0;
			Int32 cnt = (Int32)Session[ "LOGIN_COUNT" ];
			if( cnt > 2 )
			{
				Response.Write( "Attempts to login are exceeded." );
				Response.End();
			}
			else
			{
				if( FormsAuthentication.Authenticate(idLogin.Value, idPwd.Value) )
				{
					FormsAuthenticationTicket t = new FormsAuthenticationTicket( 
						1, idLogin.Value, DateTime.Now, DateTime.Now.AddMinutes(60), false, "" 
					);
					HttpCookie cook = new HttpCookie( FormsAuthentication.FormsCookieName, FormsAuthentication.Encrypt(t) );
					if( t.IsPersistent )
						cook.Expires = t.Expiration;
					cook.Path = FormsAuthentication.FormsCookiePath;
					Response.Cookies.Add( cook );

					HttpCookie cookL = new HttpCookie( "LoginCook", idLogin.Value );
					cookL.Path = "/";
					cookL.Expires = DateTime.Now.AddYears( 50 );
					Response.Cookies.Add( cookL );
					cookL = new HttpCookie( "PassCook", idPwd.Value );
					cookL.Path = "/";
					cookL.Expires = DateTime.Now.AddYears( 50 );
					Response.Cookies.Add( cookL );

					Response.Redirect( FormsAuthentication.GetRedirectUrl(idLogin.Value, t.IsPersistent), true );
				}
				else
				{
					Session[ "LOGIN_COUNT" ] = ++cnt;
					//Response.Redirect( "logon.aspx" );
					isLblErrLogin.Text = "Login and password are incorrect.";
					isLblErrLogin.Visible = true;
				}
			}

		}
	}
}
