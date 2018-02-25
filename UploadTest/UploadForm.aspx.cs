using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.IO;
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
	/// Summary description for WebForm1.
	/// </summary>
	public class UploadForm : System.Web.UI.Page
	{
		protected System.Web.UI.WebControls.Button idBtnSignOut;
		//protected System.Web.UI.HtmlControls.HtmlInputFile idFile;
		//protected System.Web.UI.HtmlControls.HtmlInputButton idSubm;

		private void DumpRequest( String fileName )
		{
			using( FileStream fs = new FileStream(fileName, FileMode.Create, FileAccess.Write, FileShare.Read) )
			{
				byte[] arr = Request.BinaryRead( Request.ContentLength );
				fs.Write( arr, 0, Request.ContentLength );
			}

            Debugger.Log( 0, "", "HEADERS:\r\n" );
            for( Int32 i = 0; i < Request.Headers.Count; ++i )
            {
                Debugger.Log( 0, "", Request.Headers.GetKey(i) + " = " );  
                Debugger.Log( 0, "", "[" + Request.Headers[i] + "]\r\n" );
            }

            Debugger.Log( 0, "", "PARAMS:\r\n" );
            foreach( String f in this.Request.Params )
            {
                Debugger.Log( 0, "", f + " = " );
                Debugger.Log( 0, "", "[" + Request[f] + "]\r\n" );
            }

            Debugger.Log( 0, "", "FILES:\r\n" );
            for( Int32 i = 0; i < Request.Files.Count; ++i )
            {
                HttpPostedFile f = Request.Files[ i ];
                Debugger.Log( 0, "", String.Format("{0} - {1} - {2}", f.ContentLength, f.ContentType, f.FileName) );
                using( FileStream fs = new FileStream(@"i:\Work\ResizerSln\upl.bin", FileMode.Create, FileAccess.Write, FileShare.Read) )
                {
                    byte[] buff = new byte[ f.ContentLength ];
                    f.InputStream.Read( buff, 0, f.ContentLength );
                    fs.Write( buff, 0, f.ContentLength );
                }
                //using( StreamReader rd = new StreamReader(f.InputStream) )
                //Debugger.Log( 0, "", "[" + rd.ReadToEnd() + "]" );
            }
		}
		private void Page_Load( object sender, System.EventArgs e )
		{
			if( this.IsPostBack )
			{
				DumpRequest( @"c:\Work\ResizerSln\req.bin" );
				return;

                Debugger.Log( 0, "", "FILES:\r\n" );
				for( Int32 i = 0; i < Request.Files.Count; ++i )
				{
					HttpPostedFile f = Request.Files[ i ];
					Debugger.Log( 0, "", String.Format("{0} - {1} - {2}", f.ContentLength, f.ContentType, f.FileName) );
					using( FileStream fs = new FileStream(@"i:\Work\ResizerSln\upl.bin", FileMode.Create, FileAccess.Write, FileShare.Read) )
					{
						byte[] buff = new byte[ f.ContentLength ];
						f.InputStream.Read( buff, 0, f.ContentLength );
						fs.Write( buff, 0, f.ContentLength );
					}
					//using( StreamReader rd = new StreamReader(f.InputStream) )
					//Debugger.Log( 0, "", "[" + rd.ReadToEnd() + "]" );
				}
                Debugger.Log( 0, "", "PARAMS:\r\n" );
				foreach( String f in this.Request.Params )
				{
					Debugger.Log( 0, "", f + " = " );
					Debugger.Log( 0, "", "[" + Request[f] + "]\r\n" );
				}

                Debugger.Log( 0, "", "HEADERS:\r\n" );
                for( Int32 i = 0; i < Request.Headers.Count; ++i )
                {
                    Debugger.Log( 0, "", Request.Headers.GetKey(i) + " = " );  
                    Debugger.Log( 0, "", "[" + Request.Headers[i] + "]\r\n" );
                }
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
			this.idBtnSignOut.Click += new System.EventHandler(this.idBtnSignOut_Click);
			this.Load += new System.EventHandler(this.Page_Load);

		}
		#endregion

		private void idBtnSignOut_Click( object sender, System.EventArgs e )
		{
			FormsAuthentication.SignOut();
			Session.Abandon();

			HttpCookie cookLogin = new HttpCookie( FormsAuthentication.FormsCookieName, "" );
			cookLogin.Expires = DateTime.Now.AddYears( -1 );
			cookLogin.Path = FormsAuthentication.FormsCookiePath;

			HttpCookie cookLogged = new HttpCookie("__logged","");
			cookLogged.Expires = DateTime.Now.AddYears( -1 );
			cookLogged.Path = FormsAuthentication.FormsCookiePath;
			Response.Cookies.Set( cookLogin );
			Response.Cookies.Add( cookLogged );

			Response.Redirect( "login.aspx", false );
		}
	}
}
