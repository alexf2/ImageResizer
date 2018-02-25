using System;
using System.Xml.Serialization;
using System.Xml;
using System.Diagnostics;
using System.Configuration;

namespace UploadTest
{
	[XmlType("user")]
	public sealed class UserItem
	{
		[XmlAttributeAttribute( AttributeName = "name") ]
		public String Name;
		[XmlAttributeAttribute( AttributeName = "roles") ]
		public String Roles;
	}
	[XmlType("UserRoles")]
	public sealed class RolesSection: IConfigurationSectionHandler
	{
		[XmlElement("user")]
		public UserItem[] Users;

		public String[] GetRolesForuser( String user )
		{
			String[] res = new String[ 0 ];
			foreach( UserItem it in Users )
				if( it.Name == user )
				{
					res = it.Roles.Split( '|' );
					break;
				}
			return res;
		}

		public RolesSection()
		{
		}

		Object IConfigurationSectionHandler.Create( Object parent, Object confCtx, XmlNode section )
		{
			XmlSerializer ser = new XmlSerializer( typeof(RolesSection) );
			return ser.Deserialize( new XmlNodeReader(section) );
		}

		private static RolesSection _self;
		static RolesSection()
		{
			_self = (RolesSection)ConfigurationSettings.GetConfig( "UserRoles" );
		}
		public static RolesSection Instance
		{
			get { return _self; }
		}
	}
}

