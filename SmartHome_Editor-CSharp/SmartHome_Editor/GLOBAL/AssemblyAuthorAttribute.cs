using System;



namespace Global.Attributes 
{
    [AttributeUsage(AttributeTargets.Assembly, AllowMultiple = false)]
    public class AssemblyAuthorAttribute : Attribute
    {
        public string AuthorName { get; }

        public AssemblyAuthorAttribute(string authorName)
        {
            AuthorName = authorName;
        }
    }
}