using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


// Damian Kujawski: Test of BTree Database, based on TXT File:
namespace BTree_Database
{
    class BTree
    {
        static void Main(string[] args)
        {
            BTree<int> _bTree = new BTree<int>(3);

            _bTree.Insert(1);
            _bTree.Insert(3);
            _bTree.Insert(7);
            _bTree.Insert(10);
            _bTree.Insert(11);

            // Save the B-tree to a file
            _bTree.SaveToFile("btree.txt");
        }
    }
}
