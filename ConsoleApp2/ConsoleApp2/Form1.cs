using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            button_start.Enabled = false;
        }

        private void button_start_Click(object sender, EventArgs e)
        {
            Form2 f2 = new Form2(textBox_ime_meni.Text, textBox_ukupno_meni.Text, textBox_ulog_meni.Text);
            f2.Show();
        }
        private void onKeyPress(object sender, KeyPressEventArgs e)
        {
            if (!Char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }
        private void onTextChanged(object sender, EventArgs e)
        {
            if ((textBox_ime_meni.Text != "" && textBox_ukupno_meni.Text != "" && textBox_ulog_meni.Text != "")&&(Int32.Parse(textBox_ukupno_meni.Text) > Int32.Parse(textBox_ulog_meni.Text)))
            {
                button_start.Enabled = true;
            }
            else
            {
                button_start.Enabled = false;
            }
        }

        private void button_izlaz_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
