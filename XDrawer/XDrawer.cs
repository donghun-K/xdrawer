namespace XDrawer
{
    public partial class XDrawer : Form
    {
        public XDrawer()
        {
            InitializeComponent();
        }

        private void XDrawer_Load(object sender, EventArgs e)
        {

        }

        private void canvas_MouseClick(object sender, MouseEventArgs e)
        {
            MessageBox.Show("X ��ǥ : " + e.X + "\nY ��ǥ : " + e.Y + "\nŬ�� ��ư : " + e.Button);
        }
    }
}