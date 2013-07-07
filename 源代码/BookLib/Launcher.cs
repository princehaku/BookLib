using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Security.Cryptography;
using Readfile;
using BookLib;
using TTS;

namespace BookLib
{
    //公共结构..用于传递后台服务器状况
    public struct server {
        public static  string text;
    }
    public partial class Launcher : Form
    {
        //public int i;
        Form1 mainform = new Form1();
        
        public Launcher()
        {
            InitializeComponent();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (progressBar1.Value == 100) 
            {
                progressBar1.Value = 0;
            }
            progressBar1.Value += 1;
            //如果线程结束则清空资源进入主窗口
            switch (progressBar1.Value)
            {
                case 1 : label3.Text = "载入配置文件";
                         break;
                case 30: label3.Text = "载入数据库";
                         speaker.speak("初始化数据库");
                         mainform.db.query("use DB");
                         break;
                case 60: label3.Text = "载入界面";
                         speaker.speak("载入界面");
                         break;
            }
            if (!backgroundWorker1.IsBusy & progressBar1.Value >= 90)
            {
                //释放线程资源
                backgroundWorker1.CancelAsync();
                backgroundWorker1.Dispose();
                this.Hide();
                this.ShowInTaskbar = false;
                mainform.Show();
                timer1.Enabled = false;
            }
            
            
        }

        private void Launcher_Load(object sender, EventArgs e)
        {
            
            speaker.speak("请输入用户名和密码;"); 
            mainform.db = new DBcore.DBcore(".\\");
            //mainform.db = new DBcore.DBcore(".\\");
            //mainform.db.query("use DB");
            //mainform.db.query("insert into `book` values ('3','汇编','电子电工类的专业书..优秀的课本','老师','电子工业出版社','电子类','5','3')");
            //mainform.db.query("select from `book` where `id`='3')");
            //mainform.db.fetchline();
            //MessageBox.Show(mainform.db.get("booktitle"));
        }
        //混合密码
        public static string GetMd6Str(string ConvertString)
        {
            MD5CryptoServiceProvider md5 = new MD5CryptoServiceProvider();
            string t2 = BitConverter.ToString(md5.ComputeHash(UTF8Encoding.Default.GetBytes(ConvertString)), 4, 8).Replace("-", "B");
            t2 += BitConverter.ToString(md5.ComputeHash(UTF8Encoding.Default.GetBytes(ConvertString)), 4, 8).Replace("-","Z");
            t2 += BitConverter.ToString(md5.ComputeHash(UTF8Encoding.Default.GetBytes(ConvertString)), 4, 8).Replace("-", "W");
            return t2;
        }

        //废弃
        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            //在此载入数据库
        }

        private void button1_Click(object sender, EventArgs e)
        {            
            groupBox1.Enabled =false ;
            //配置文件读取类
            Readfile.Readfile cfg = new Readfile.Readfile();
            
            button1.Enabled = false;
            //检验用户名和密码
            string user=cfg.GetConfig(Application.StartupPath + "/DB/PWD.mdb", "username");

            string pwd = cfg.GetConfig(Application.StartupPath + "/DB/PWD.mdb", "userpassword");

            if (GetMd6Str(textBox1.Text) == user && GetMd6Str(textBox2.Text) == pwd)
            {
                this.Focus();
                //改变鼠标形状
                this.Cursor = System.Windows.Forms.Cursors.WaitCursor;
                progressBar1.Visible = true;
                button1.Visible = false;
                timer1.Enabled = true;
                backgroundWorker1.RunWorkerAsync();
                speaker.speak("登陆成功;请稍后");
                if (cfg.GetConfig(Application.StartupPath + "/config.inc", "dbroot") == "null")
                {
                    mainform.db.query("create database DB");
                    mainform.db.query("use DB");
                    mainform.db.query("create table `book` (`id` key,`booktitle` text,`description` text,`writer` int,`publisher` text,`type` text,`store` int,`nums` int)");
                    mainform.db.query("create table `lendinfo` (`id` key,`bookid` int,`readerid` int)");
                    //mainform.db.query("create table `writer` (`wid` key,`name` text,`sex` text,`description` text)");
                    mainform.db.query("create table `reader` (`sid` key,`name` text,`sex` text,`maxnum` int,`lending` int,`owe` double)");
                    //mainform.db.query("create table `publisher` (`pid` key,`booktitle` text,`publisher` text,`type` text,`writer` text,`maxnums` int,`lendnums` int)");
                    cfg.AddDetail(Application.StartupPath + "/config.inc", "dbroot");
                 }
            }
            else
            {
                label3.Text = "用户名或密码错误";
                speaker.speak("用户名或密码错误;请重新输入");
                timer2.Enabled = true;
            }
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            groupBox1.Enabled = true;
            button1.Enabled = true;
            label3.Text = "";
            timer2.Enabled = false;
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            mainform.Dispose();
            Application.Exit();
        }

        private void Launcher_Paint(object sender, PaintEventArgs e)
        {
            //设定交点 
            if (textBox1.Text=="") { textBox1.Focus(); }
        }

       

      
    }
}
