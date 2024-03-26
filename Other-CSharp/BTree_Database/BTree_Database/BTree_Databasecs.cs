using System;
using System.IO;

using BTree_Database.BTree_;



namespace BTree_Database
{
    internal class BTree<T> where T : IComparable<T>
    {
        private BTreeNode<T> root_;
        private readonly int degree_;

        public BTree(int degree)
        {
            this.degree_ = degree;
            root_ = new BTreeNode<T>(degree);
        }

        public void Insert(T key)
        {
            if (root_.Keys.Count == (2 * degree_) - 1)
            {
                BTreeNode<T> newRoot = new BTreeNode<T>(degree_);
                newRoot.Children.Add(root_);
                SplitChild(newRoot, 0);
                root_ = newRoot;
            }
            InsertNonFull(root_, key);
        }

        private void InsertNonFull(BTreeNode<T> node, T key)
        {
            int _index = node.Keys.Count - 1;

            if (node.IsLeaf)
            {
                while (_index >= 0 && key.CompareTo(node.Keys[_index]) < 0)
                {
                    _index--;
                }
                node.Keys.Insert(_index + 1, key);
            }
            else
            {
                while (_index >= 0 && key.CompareTo(node.Keys[_index]) < 0)
                {
                    _index--;
                }
                _index++;

                if (node.Children[_index].Keys.Count == (2 * degree_) - 1)
                {
                    SplitChild(node, _index);
                    if (key.CompareTo(node.Keys[_index]) > 0)
                    {
                        _index++;
                    }
                }
                InsertNonFull(node.Children[_index], key);
            }
        }

        private void SplitChild(BTreeNode<T> parent, int childIndex)
        {
            BTreeNode<T> _child = parent.Children[childIndex];
            BTreeNode<T> _newChild = new BTreeNode<T>(degree_);
            _newChild.IsLeaf = _child.IsLeaf;

            for (int i = 0; i < degree_ - 1; i++)
            {
                _newChild.Keys.Add(_child.Keys[degree_ + i]);
                _child.Keys.RemoveAt(degree_ + i);
            }

            if (!_child.IsLeaf)
            {
                for (int i = 0; i < degree_; i++)
                {
                    _newChild.Children.Add(_child.Children[degree_ + i]);
                }
                _child.Children.RemoveRange(degree_, degree_);
            }

            parent.Keys.Insert(childIndex, _child.Keys[degree_ - 1]);
            parent.Children.Insert(childIndex + 1, _newChild);
            _child.Keys.RemoveAt(degree_ - 1);
        }

        public void Traverse()
        {
            Traverse(root_);
        }

        private void Traverse(BTreeNode<T> node)
        {
            if (node != null)
            {
                for (int i = 0; i < node.Keys.Count; i++)
                {
                    Traverse(node.Children[i]);
                    Console.Write(node.Keys[i] + " ");
                }
                Traverse(node.Children[node.Keys.Count]);
            }
        }

        public void SaveToFile(string fileName)
        {
            using (StreamWriter writer = new StreamWriter(fileName))
            {
                SaveNodeToFile(root_, writer);
            }
        }

        private void SaveNodeToFile(BTreeNode<T> node, StreamWriter writer)
        {
            if (node != null)
            {
                writer.WriteLine(string.Join(" ", node.Keys));
                foreach (BTreeNode<T> child in node.Children)
                {
                    SaveNodeToFile(child, writer);
                }
            }
        }

        public void LoadFromFile(string fileName)
        {
            root_ = null; // Clear existing tree
            using (StreamReader reader = new StreamReader(fileName))
            {
                while (!reader.EndOfStream)
                {
                    string line = reader.ReadLine();
                    string[] keys = line.Split(' ');
                    foreach (string key in keys)
                    {
                        Insert((T)Convert.ChangeType(key, typeof(T)));
                    }
                }
            }
        }
    }

}
