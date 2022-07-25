
namespace Lab2
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox_meni = new System.Windows.Forms.GroupBox();
            this.textBox_ime_meni = new System.Windows.Forms.TextBox();
            this.label_ime = new System.Windows.Forms.Label();
            this.button_zatvori_meni = new System.Windows.Forms.Button();
            this.button_start = new System.Windows.Forms.Button();
            this.textBox_ulog_meni = new System.Windows.Forms.TextBox();
            this.textBox_ukupno_meni = new System.Windows.Forms.TextBox();
            this.label_ulog_meni = new System.Windows.Forms.Label();
            this.label_poeni_meni = new System.Windows.Forms.Label();
            this.groupBox_meni.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox_meni
            // 
            this.groupBox_meni.Controls.Add(this.textBox_ime_meni);
            this.groupBox_meni.Controls.Add(this.label_ime);
            this.groupBox_meni.Controls.Add(this.button_zatvori_meni);
            this.groupBox_meni.Controls.Add(this.button_start);
            this.groupBox_meni.Controls.Add(this.textBox_ulog_meni);
            this.groupBox_meni.Controls.Add(this.textBox_ukupno_meni);
            this.groupBox_meni.Controls.Add(this.label_ulog_meni);
            this.groupBox_meni.Controls.Add(this.label_poeni_meni);
            this.groupBox_meni.Location = new System.Drawing.Point(128, 64);
            this.groupBox_meni.Name = "groupBox_meni";
            this.groupBox_meni.Size = new System.Drawing.Size(506, 286);
            this.groupBox_meni.TabIndex = 0;
            this.groupBox_meni.TabStop = false;
            this.groupBox_meni.Text = "Meni";
            // 
            // textBox_ime_meni
            // 
            this.textBox_ime_meni.Location = new System.Drawing.Point(195, 41);
            this.textBox_ime_meni.Name = "textBox_ime_meni";
            this.textBox_ime_meni.Size = new System.Drawing.Size(100, 23);
            this.textBox_ime_meni.TabIndex = 6;
            this.textBox_ime_meni.TextChanged += new System.EventHandler(this.onTextChanged);
            // 
            // label_ime
            // 
            this.label_ime.AutoSize = true;
            this.label_ime.Location = new System.Drawing.Point(139, 44);
            this.label_ime.Name = "label_ime";
            this.label_ime.Size = new System.Drawing.Size(30, 15);
            this.label_ime.TabIndex = 5;
            this.label_ime.Text = "Ime:";
            // 
            // button_zatvori_meni
            // 
            this.button_zatvori_meni.Location = new System.Drawing.Point(425, 22);
            this.button_zatvori_meni.Name = "button_zatvori_meni";
            this.button_zatvori_meni.Size = new System.Drawing.Size(75, 23);
            this.button_zatvori_meni.TabIndex = 4;
            this.button_zatvori_meni.Text = "Izlaz";
            this.button_zatvori_meni.UseVisualStyleBackColor = true;
            this.button_zatvori_meni.Click += new System.EventHandler(this.button_izlaz_Click);
            // 
            // button_start
            // 
            this.button_start.AccessibleRole = System.Windows.Forms.AccessibleRole.IpAddress;
            this.button_start.Location = new System.Drawing.Point(209, 184);
            this.button_start.Name = "button_start";
            this.button_start.Size = new System.Drawing.Size(75, 36);
            this.button_start.TabIndex = 1;
            this.button_start.Text = "START";
            this.button_start.UseVisualStyleBackColor = true;
            this.button_start.Click += new System.EventHandler(this.button_start_Click);
            // 
            // textBox_ulog_meni
            // 
            this.textBox_ulog_meni.Location = new System.Drawing.Point(195, 127);
            this.textBox_ulog_meni.Name = "textBox_ulog_meni";
            this.textBox_ulog_meni.Size = new System.Drawing.Size(100, 23);
            this.textBox_ulog_meni.TabIndex = 3;
            this.textBox_ulog_meni.TextChanged += new System.EventHandler(this.onTextChanged);
            this.textBox_ulog_meni.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.onKeyPress);
            // 
            // textBox_ukupno_meni
            // 
            this.textBox_ukupno_meni.Location = new System.Drawing.Point(195, 86);
            this.textBox_ukupno_meni.Name = "textBox_ukupno_meni";
            this.textBox_ukupno_meni.Size = new System.Drawing.Size(100, 23);
            this.textBox_ukupno_meni.TabIndex = 2;
            this.textBox_ukupno_meni.TextChanged += new System.EventHandler(this.onTextChanged);
            this.textBox_ukupno_meni.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.onKeyPress);
            // 
            // label_ulog_meni
            // 
            this.label_ulog_meni.AutoSize = true;
            this.label_ulog_meni.Location = new System.Drawing.Point(134, 130);
            this.label_ulog_meni.Name = "label_ulog_meni";
            this.label_ulog_meni.Size = new System.Drawing.Size(35, 15);
            this.label_ulog_meni.TabIndex = 1;
            this.label_ulog_meni.Text = "Ulog:";
            // 
            // label_poeni_meni
            // 
            this.label_poeni_meni.AutoSize = true;
            this.label_poeni_meni.Location = new System.Drawing.Point(82, 89);
            this.label_poeni_meni.Name = "label_poeni_meni";
            this.label_poeni_meni.Size = new System.Drawing.Size(87, 15);
            this.label_poeni_meni.TabIndex = 0;
            this.label_poeni_meni.Text = "Ukupno novca:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.groupBox_meni);
            this.Name = "Form1";
            this.Text = "Meni";
            this.groupBox_meni.ResumeLayout(false);
            this.groupBox_meni.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox_meni;
        private System.Windows.Forms.Label label_ulog_meni;
        private System.Windows.Forms.Label label_poeni_meni;
        private System.Windows.Forms.TextBox textBox_ulog_meni;
        private System.Windows.Forms.TextBox textBox_ukupno_meni;
        private System.Windows.Forms.Button button_zatvori_meni;
        private System.Windows.Forms.Button button_start;
        private System.Windows.Forms.TextBox textBox_ime_meni;
        private System.Windows.Forms.Label label_ime;
    }
}

