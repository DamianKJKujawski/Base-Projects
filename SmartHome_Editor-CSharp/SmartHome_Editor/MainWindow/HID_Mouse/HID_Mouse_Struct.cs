
namespace SmartHome_Editor.HID_Mouse_
{
    public struct MouseButton
    {
        public bool pressed;
        public bool selecting;

        public System.Windows.Point position;


        public MouseButton()
        {
            pressed = false;
            selecting = false;

            position = new System.Windows.Point(-1.0f, -1.0f);
        }
    };
}
