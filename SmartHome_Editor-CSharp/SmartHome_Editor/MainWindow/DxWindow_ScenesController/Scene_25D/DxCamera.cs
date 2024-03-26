using SharpDX;



namespace DxWindow.ScenesController.Scene_25D
{
    public class DxCamera
    {
        #region VARIABLES:

            // Positioning:
            private Vector3 position_ = new ();
            private Vector3 rotation_ = new ();

            // Projection:
            public Matrix ViewMatrix { get; private set; }
            public Matrix ProjectionMatrix { get; private set; }

        #endregion



        #region INIT/DISPOSAL:

            public DxCamera() {}

        #endregion



        #region PUBLIC:

            public void Set_ProjectionMatrix(SharpDX.Matrix projection)
            {
                ProjectionMatrix = projection;
            }


            public void Set_Position(float x, float y, float z)
            {
                position_.X = x;
                position_.Y = y;
                position_.Z = z;
            }

            public void Move_Position(float x, float y, float z = 0)
            {
                float _scaleZ = 7.0f + position_.Z;

                position_.X += x / _scaleZ;
                position_.Y += y / _scaleZ;
                position_.Z += z;
            }

            public float Zoom_UsingAxisZ(float z)
            {
                position_.Z += z;

                if (position_.Z > -1.5f)
                    position_.Z = -1.5f;

                if (position_.Z < -5.5f)
                    position_.Z = -5.5f;

                return position_.Z;
            }


            public Vector3 Get_LookAt_OnThePlaneZ0(Vector2 screenPoint, int screenWidth, int screenHeight)
            {
                float normalizedX = (2.0f * screenPoint.X) / screenWidth - 1.0f;
                float normalizedY = 1.0f - (2.0f * screenPoint.Y) / screenHeight;

                // Create near and far points in clip space:
                Vector4 nearPoint = new (normalizedX, normalizedY, 0, 1.0f);
                Vector4 farPoint = new (normalizedX, normalizedY, 1, 1.0f);

                // Transform the points to world space:
                Matrix viewProjectionInverse = Matrix.Invert(ViewMatrix * ProjectionMatrix);
                Vector4 nearPointWorld = Vector4.Transform(nearPoint, viewProjectionInverse);
                Vector4 farPointWorld = Vector4.Transform(farPoint, viewProjectionInverse);

                // Normalize the vectors:
                Vector3 nearPoint3D = new (nearPointWorld.X / nearPointWorld.W, nearPointWorld.Y / nearPointWorld.W, nearPointWorld.Z / nearPointWorld.W);
                Vector3 farPoint3D = new (farPointWorld.X / farPointWorld.W, farPointWorld.Y / farPointWorld.W, farPointWorld.Z / farPointWorld.W);

                // Calculate the ray direction:
                Vector3 rayDirection = Vector3.Normalize(farPoint3D - nearPoint3D);

                // Calculate intersection point with the plane z = 0:
                float t = -nearPoint3D.Z / rayDirection.Z;
                Vector3 intersectionPoint = nearPoint3D + t * rayDirection;

                return intersectionPoint;
            }


            public void Render()
            {
                // Set the position of the camera in the world:
                Vector3 _position = new(position_.X, position_.Y, position_.Z);

                // Set where the camera is looking by default:
                Vector3 lookAt = new(0, 0, 1);

                // Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians:
                float pitch = rotation_.X * 0.0174532925f;
                float yaw = rotation_.Y * 0.0174532925f; ;
                float roll = rotation_.Z * 0.0174532925f; ;

                // Create the rotation matrix:
                Matrix rotationMatrix = Matrix.RotationYawPitchRoll(yaw, pitch, roll);

                // Transform the lookAt and up vector by the rotation matrix:
                lookAt = Vector3.TransformCoordinate(lookAt, rotationMatrix);
                Vector3 up = Vector3.TransformCoordinate(Vector3.UnitY, rotationMatrix);

                // Translate the rotated camera position:
                lookAt = _position + lookAt;

                // Create the view matrix:
                ViewMatrix = Matrix.LookAtLH(_position, lookAt, up);
            }

        #endregion
    }
}