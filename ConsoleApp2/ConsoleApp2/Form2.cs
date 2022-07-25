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
    public partial class Form2 : Form
    {
        private Karta glavna;
        private int cekirani;
        private int kvota;
        private int ulog_int;
        private int ukupno_int;
        private int dobitak;
        private int pom = 0;
        public Form2(string ime, string ukupno, string ulog)
        {
            InitializeComponent();
            groupBox_karte.Hide();
            textBox_ime_igra.Text = ime;
            textBox_ukupno_igra.Text = ukupno;
            textBox_ulog_igra.Text = ulog;
            ukupno_int = Int32.Parse(ukupno);
            ulog_int = Int32.Parse(ulog);
            kvota = 0;
            dobitak = 0;
        }

        private void button_zatvori_igra_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button_zavrti_Click(object sender, EventArgs e)
        {
            button_zatvori_igra.Hide();
            groupBox_karte.Show();
            Ocekiraj();
            cekirani = 0;
            glavna = new Karta();
            Podesi_karte();
            button_zameni.Enabled = false;           
            button_zavrti.Hide();
            kvota = glavna.Kvota();
            dobitak = ulog_int * kvota;
            textBox_dobitak.Text = dobitak.ToString();
            pom = 1;
        }

        private void button_izlaz_karte_Click(object sender, EventArgs e)
        {
            groupBox_karte.Hide();
            button_zavrti.Show();
            button_zatvori_igra.Show();
        }
        public void Ocekiraj()
        {
            checkBox_k1.Checked = false;
            checkBox_k2.Checked = false;
            checkBox_k3.Checked = false;
            checkBox_k4.Checked = false;
            checkBox_k5.Checked = false;
        }
        private void button_nova_ruka_Click(object sender, EventArgs e)
        {
            if(pom == 1){
                ukupno_int = ukupno_int + dobitak - ulog_int;
                button_nova_ruka.Enabled = true;
                textBox_ukupno_igra.Text = ukupno_int.ToString();
                pom = 0;
            }
            
            if (Int32.Parse(textBox_ulog_igra.Text) > Int32.Parse(textBox_ukupno_igra.Text))
            {
                button_zameni.Hide();
                checkBox_k1.Hide();
                checkBox_k2.Hide();
                checkBox_k3.Hide();
                checkBox_k4.Hide();
                checkBox_k5.Hide();
                button_nova_ruka.Hide();
            }
            else
            {
                Ocekiraj();
                Podesi_karte();
                kvota = glavna.Kvota();
                dobitak = ulog_int * kvota;
                textBox_dobitak.Text = dobitak.ToString();

                button_zameni.Enabled = false;
                pom = 1;
            }
        }
        public void Podesi_karte()
        {
            cekirani = 0;
            glavna = new Karta();
            String pom;
            pom = glavna.Vrati_putanju();
            pictureBox_k1.Image = Image.FromFile(pom);
            pom = glavna.Vrati_putanju();
            pictureBox_k2.Image = Image.FromFile(pom);
            pom = glavna.Vrati_putanju();
            pictureBox_k3.Image = Image.FromFile(pom);
            pom = glavna.Vrati_putanju();
            pictureBox_k4.Image = Image.FromFile(pom);
            pom = glavna.Vrati_putanju();
            pictureBox_k5.Image = Image.FromFile(pom);
            
        }

        private void button_zameni_Click(object sender, EventArgs e)
        {
            if (cekirani <= 3)
            { 
                string pom2;
                int sma = 0;
                if (checkBox_k1.Checked){
                    glavna.izbaci(0 - sma);
                    sma++;
                    pom2 = glavna.Vrati_putanju();
                    pictureBox_k1.Image = Image.FromFile(pom2);
                }
                if (checkBox_k2.Checked){
                    glavna.izbaci(1 - sma);
                    sma++;
                    pom2 = glavna.Vrati_putanju();
                    pictureBox_k2.Image = Image.FromFile(pom2);
                }
                if (checkBox_k3.Checked){
                    glavna.izbaci(2 - sma);
                    sma++;
                    pom2 = glavna.Vrati_putanju();
                    pictureBox_k3.Image = Image.FromFile(pom2);
                }
                if (checkBox_k4.Checked){
                    glavna.izbaci(3 - sma);
                    sma++;
                    pom2 = glavna.Vrati_putanju();
                    pictureBox_k4.Image = Image.FromFile(pom2);
                }
                if (checkBox_k5.Checked){
                    glavna.izbaci(4 - sma);;
                    pom2 = glavna.Vrati_putanju();
                    pictureBox_k5.Image = Image.FromFile(pom2);
                }
                button_zameni.Enabled = false;
                kvota = glavna.Kvota();
                dobitak = ulog_int * kvota;
                textBox_dobitak.Text = dobitak.ToString();
                pom = 1;
            }       
        }
        private void checkBox_k1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox_k1.Checked){
                cekirani++;
                button_zameni.Enabled = true;
            }
            else
            {
                cekirani--;
            }
        }

        private void checkBox_k2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox_k2.Checked){
                cekirani++;
                button_zameni.Enabled = true;
            }
            else
            {
                cekirani--;
            }
        }

        private void checkBox_k3_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox_k3.Checked){
                cekirani++;
                button_zameni.Enabled = true;
            }
            else
            {
                cekirani--;
            }
        }

        private void checkBox_k4_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox_k4.Checked){
                cekirani++;
                button_zameni.Enabled = true;
            }
            else
            {
                cekirani--;
            }
        }

        private void checkBox_k5_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox_k5.Checked){
                cekirani++;
                button_zameni.Enabled = true;
            }
            else
            {
                cekirani--;
            }
        }
    }
}
