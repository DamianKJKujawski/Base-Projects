using System;

using SharpDX;
using DxWindow.ScenesController.Scene_25D.IsometricMath_;



namespace DxWindow.ScenesController.Scene_25D
{
    internal static class IsometricMath
    {
        // 2.5D Matrix - rotated 45 degrees:
        // "X" and "Y" are 2D Matrix indices and "Z" is real "height" parameter
        #region PUBLIC:

            public static Vector2 Calculate_PointUsingMatrixIndices(float idx_x, float idx_y)
            {
                float _coordinateX = 0.4f * (idx_x - idx_y);
                float _coordinateY = 0.2f * (idx_x + idx_y);

                return new Vector2(_coordinateX, _coordinateY);
            }

            public static IsometricModelPoints Calculate_ModelPoints(Vector3 position, Vector2 size)
            {
                IsometricModelPoints _isometricModelPoints;

                Vector2 _point = Calculate_PointUsingMatrixIndices(position.X, position.Y);
                _isometricModelPoints.p0.X = _point.X;
                _isometricModelPoints.p0.Y = _point.Y;

                _point = Calculate_PointUsingMatrixIndices(position.X, position.Y + size.Y);
                _isometricModelPoints.p1.X = _point.X;
                _isometricModelPoints.p1.Y = _point.Y;

                _point = Calculate_PointUsingMatrixIndices(position.X + size.X, position.Y);
                _isometricModelPoints.p2.X = _point.X;
                _isometricModelPoints.p2.Y = _point.Y;

                _point = Calculate_PointUsingMatrixIndices(position.X + size.X, position.Y + size.Y);
                _isometricModelPoints.p3.X = _point.X;
                _isometricModelPoints.p3.Y = _point.Y;

                return _isometricModelPoints;
            }

            public static Vector3 Get_MatrixIndicesUsingPoint(float x, float y)
            {
                y *= 2;

                double _rotationDegrees = -45.0;

                double _rotationRadians = _rotationDegrees * Math.PI / 180.0;

                // Obliczenie nowych współrzędnych po obrocie
                float newX = (float)(x * Math.Cos(_rotationRadians) - y * Math.Sin(_rotationRadians));
                float newY = (float)(x * Math.Sin(_rotationRadians) + y * Math.Cos(_rotationRadians));

                double _div = Math.Sqrt(0.32);

                if (newX < 0)
                    newX = -1;
                else
                    newX = (int)(newX / _div);

                if (newY < 0)
                    newY = -1;
                else
                    newY = (int)(newY / _div);

                return new Vector3(newX, newY, -0.01f);
            }

        #endregion
    }
}
