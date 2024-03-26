using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BTree_Database.BTree_
{
    public class BTreeNode<T> where T : IComparable<T>
    {
        public List<T> Keys { get; private set; }
        public List<BTreeNode<T>> Children { get; private set; }
        public bool IsLeaf { get; set; }

        public BTreeNode(int degree)
        {
            Keys = new List<T>();
            Children = new List<BTreeNode<T>>();
            IsLeaf = true;
        }

        public int GetChildIndex(T key)
        {
            int index = 0;
            while (index < Keys.Count && key.CompareTo(Keys[index]) > 0)
            {
                index++;
            }
            return index;
        }
    }
}
