using Global.Attributes;
using System.Reflection;



namespace Global.Config
{
    public static class FilePath
    {
        public const string shader = @".\";
    }

    public static class Project
    {
        public static string Author { get; private set; }
        public static System.Version? Version { get; private set; }


        private static string Get_Author(Assembly assembly)
        {
            string _authorName = string.Empty;

            object[] attributes = assembly.GetCustomAttributes(typeof(AssemblyAuthorAttribute), false);

            if (attributes.Length > 0)
            {
                AssemblyAuthorAttribute _authorAttribute = (AssemblyAuthorAttribute)attributes[0];

                _authorName = _authorAttribute.AuthorName;

            }

            return _authorName;
        }

        private static System.Version? Get_Version(Assembly assembly)
        {
            return assembly.GetName().Version;
        }
            
        static Project() 
        {
            Assembly _assembly = Assembly.GetExecutingAssembly();
            Author = Get_Author(_assembly);
            Version = Get_Version(_assembly);
        }
    }
}