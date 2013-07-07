using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DBcore;
using TTS;
using Readfile;

namespace BookLib
{

    public partial class Form1 : Form
    {
        public DBcore.DBcore db;

        public Form1()
        {
            InitializeComponent();
            db = new DBcore.DBcore(".\\");
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            db.query("use DB");
            //db.query("insert into `book` values ('1','电子电工技术','电子电工类的专业书..优秀的课本','老师','电子工业出版社','电子类','3','5')");

        }
        //强制退出
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Application.Exit();
        }
        //查询图书
        private void button1_Click(object sender, EventArgs e)
        {
            bookresult.Rows.Clear();
            if (textBox1.Text != "")
            {
                db.query("select from `book` where `id`='" + textBox1.Text + "'");
            }
            if (textBox2.Text != "")
            {
                db.query("select from `book` where `booktitle`='" + textBox2.Text + "'");
            }
            if (textBox3.Text != "")
            {
                db.query("select from `book` where `publisher`='" + textBox3.Text + "'");
            }
            if (textBox12.Text != "")
            {
                db.query("select from `book` where `writer`='" + textBox12.Text + "'");
            }
            if (textBox11.Text != "")
            {
                db.query("select from `book` where `type`='" + textBox11.Text + "'");
            }
            if (textBox18.Text != "")
            {
                int i = int.Parse(textBox18.Text) - 1;
                db.query("select from `book` where `id`>'" + i.ToString() + "'");
            }
            if (textBox19.Text != "")
            {
                int i = int.Parse(textBox19.Text) + 1;
                db.query("select from `book` where `id`<'" + i.ToString() + "'");
            }
            while (db.fetchline())
            {
                string id = db.get("id");
                string booktitle = db.get("booktitle");
                string description = db.get("description");
                string writer = db.get("writer");
                string publisher = db.get("publisher");
                string type = db.get("type");
                string store = db.get("store");
                string nums = db.get("nums");
                DataGridViewRow row = new DataGridViewRow();
                row.CreateCells(bookresult);
                row.Cells[0].Value = id;
                row.Cells[1].Value = booktitle;
                row.Cells[2].Value = description;
                row.Cells[3].Value = writer;
                row.Cells[4].Value = publisher;
                row.Cells[5].Value = type;
                row.Cells[6].Value = store;
                row.Cells[7].Value = nums;
                bookresult.Rows.Add(row);
            }
            bookresult.Visible = true;
        }
        //隐藏结果框
        private void tabControl1_MouseClick(object sender, MouseEventArgs e)
        {
            bookresult.Visible = false;
            readerresult.Visible = false;
        }
        //添加新图书
        private void button2_Click(object sender, EventArgs e)
        {
            if (new_bookid.Text == "")
            {
                MessageBox.Show("请填写书号");
                return;
            }
            try
            {
                db.query("insert into `book` values ('" + new_bookid.Text + "','" + new_bookname.Text + "','" + new_bookdes.Text + "','" + new_writer.Text + "','" + new_publisher.Text + "','" + new_cate.Text + "','" + new_nums.Text + "','" + new_nums.Text + "')");
                speaker.speak("新图书添加成功");
            }
            catch (Exception ex)
            {
                speaker.speak("新图书添加失败");
            }
        }
        
        //删除图书
        private void button3_Click(object sender, EventArgs e)
        {

            if (textBox8.Text != "")
            {
                try
                {
                    db.query("select from `book` where `id`='" + textBox8.Text + "'");
                    if (db.fetchline())
                    {
                        string store = db.get("store");
                        string nums = db.get("nums");
                        if (store != nums)
                        {
                            speaker.speak("图书尚有未归还;无法删除");
                            return;
                        }
                        db.query("delete from `book` where `id`='" + textBox8.Text + "'");
                        speaker.speak("图书注销成功");
                        return;
                    }
                    else
                    {
                        speaker.speak("此图书不存在");
                        return;
                    }
                }
                catch (System.Exception ex)
                {
                    speaker.speak("此图书不存在");
                    return;
                }

            }
            else
            {
                speaker.speak("请输入书号");
            }
        }

        //新读者添加
        private void button4_Click(object sender, EventArgs e)
        {
            try
            {
                db.query("insert into `reader` values ('" + textBox13.Text + "','" + textBox10.Text + "','" + comboBox1.Text + "','" + textBox4.Text + "','0','0')");
                speaker.speak("新读者添加成功");
            }
            catch (Exception ex)
            {
                speaker.speak("新读者添加失败;学号已经存在");
            }
        }


        private void comboBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            e.Handled = true;
        }

        //借阅图书
        private void button5_Click(object sender, EventArgs e)
        {
            int nums;

            try
            {
                nums = int.Parse(textBox5.Text);
            }
            catch (System.Exception ex)
            {
                speaker.speak("请输入正确的数量");
                return;
            }
            //得到学生资料
            string sid = textBox7.Text;
            db.query("select from `reader` where `sid`='" + sid + "'");
            string sname = "";
            string ssex = "";
            string smaxnum = "";
            string slending = "";
            string sowe = "";
            int slend = 0;
            if (db.fetchline())
            {
                sname = db.get("name");
                ssex = db.get("sex");
                smaxnum = db.get("maxnum");
                slending = db.get("lending");
                sowe = db.get("owe");
                slend = int.Parse(slending);
                int snum = int.Parse(smaxnum);
                //如果过多
                if (slend + nums > snum)
                {
                    speaker.speak("该读者不能再借");
                    return;
                }
                slend = slend + nums;
            }
            else
            {
                speaker.speak("此读者不存在");
                return;
            }
            //得到图书资料
            string bid = textBox6.Text;
            string booktitle = "无";
            string description = "无";
            string writer = "无";
            string publisher = "无";
            string type = "无";
            string store = "0";
            string bnums = "0";
            int bstore = 0;
            db.query("select from `book` where `id`='" + bid + "'");
            if (db.fetchline())
            {
                booktitle = db.get("booktitle");
                description = db.get("description");
                writer = db.get("writer");
                publisher = db.get("publisher");
                type = db.get("type");
                store = db.get("store");
                bnums = db.get("nums");
                bstore = int.Parse(store);
                if (bstore - nums < 0)
                {
                    speaker.speak("库存不足");
                    return;
                }
                bstore = bstore - nums;
            }
            else
            {
                speaker.speak("此图书不存在");
                return;
            }

            DateTime t1 = new DateTime(1970, 1, 1);
            DateTime t2 = DateTime.Now;
            long a = t2.Ticks - t1.Ticks / 1000;
            int yy = (int)a;
            int i = 0;
            for (i = 0; i < nums; i++)
            {
            //重复..直到插入成功
            d:
                try
                {
                    db.query("insert into `lendinfo` values ('" + yy + "','" + bid + "','" + sid + "')");
                }
                catch (Exception ex)
                {
                    yy++;
                    goto d;
                }
            }
            db.query("delete from `reader` where `sid`='" + sid + "'");
            db.query("insert into `reader` values ('" + sid + "','" + sname + "','" + ssex + "','" + smaxnum + "','" + slend + "','" + sowe + "')");
            db.query("delete from `book` where `id`='" + bid + "'");
            db.query("insert into `book` values ('" + bid + "','" + booktitle + "','" + description + "','" + writer + "','" + publisher + "','" + type + "','" + bstore.ToString() + "','" + bnums + "')");
            speaker.speak("操作成功");
        }

        private void textBox6_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar < 59 && e.KeyChar > 47 || e.KeyChar == 8)
            {
                e.Handled = false;
            }
            else
            {
                e.Handled = true;
            }
        }
        private void button7_Click(object sender, EventArgs e)
        {

            int nums;

            try
            {
                nums = int.Parse(textBox15.Text);
            }
            catch (System.Exception ex)
            {
                speaker.speak("请输入正确的数量");
                return;
            }
            //得到学生资料
            string sid = textBox17.Text;
            db.query("select from `reader` where `sid`='" + sid + "'");
            string sname = "";
            string ssex = "";
            string smaxnum = "";
            string slending = "";
            string sowe = "";
            int slend = 0;
            if (db.fetchline())
            {
                sname = db.get("name");
                ssex = db.get("sex");
                smaxnum = db.get("maxnum");
                slending = db.get("lending");
                sowe = db.get("owe");
                slend = int.Parse(slending);
                int snum = int.Parse(smaxnum);
                slend = slend - nums;
                if (slend < 0)
                {
                    speaker.speak("数量出错");
                    return;
                }
            }
            else
            {
                speaker.speak("此读者不存在");
                return;
            }
            //得到图书资料
            string bid = textBox16.Text;
            string booktitle = "";
            string description = "";
            string writer = "";
            string publisher = "";
            string type = "";
            string store = "";
            string bnums = "";
            int bstore = 0;
            db.query("select from `book` where `id`='" + bid + "'");
            if (db.fetchline())
            {
                booktitle = db.get("booktitle");
                description = db.get("description");
                writer = db.get("writer");
                publisher = db.get("publisher");
                type = db.get("type");
                store = db.get("store");
                bnums = db.get("nums");
                bstore = int.Parse(store);
                bstore = bstore + nums;
                if (bstore > int.Parse(bnums))
                {
                    speaker.speak("数量出错");
                    return;
                }
            }
            else
            {
                speaker.speak("此图书不存在");
                return;
            }
            //检测图书是否是该读者所借
            DBcore.DBcore db2 = new DBcore.DBcore(".\\");
            db2.query("use DB");
            db2.query("select from `lendinfo` where `readerid`='" + sid + "'");
            int isyours=0;
            System.Collections.ArrayList lendid=new System.Collections.ArrayList();
            while(db2.fetchline())
            {
                if(db2.get("bookid")==bid)
                {
                    isyours=1;
                    lendid.Add(db2.get("id"));
                }
            }
            if(isyours==0)
            {
                speaker.speak("该书非该读者拥有");
                return;
            }
            DateTime t1 = new DateTime(1970, 1, 1);
            DateTime t2 = DateTime.Now;
            long a = t2.Ticks - t1.Ticks / 1000;
            int yy = (int)a;
            int i = 0;
            //清理图书借阅单
            for (i = 0; i < nums; i++)
            {
                db.query("delete from `lendinfo` where `id`='" + lendid[i] + "'");
            }
            db.query("delete from `reader` where `sid`='" + sid + "'");
            
            db.query("insert into `reader` values ('" + sid + "','" + sname + "','" + ssex + "','" + smaxnum + "','" + slend + "','" + sowe + "')");
            
            db.query("delete from `book` where `id`='" + bid + "'");
            
            db.query("insert into `book` values ('" + bid + "','" + booktitle + "','" + description + "','" + writer + "','" + publisher + "','" + type + "','" + bstore.ToString() + "','" + bnums + "')");
            
            speaker.speak("操作成功");
        }

        private void button6_Click(object sender, EventArgs e)
        {
            readerresult.Rows.Clear();
            if (textBox9.Text != "")
            {
                db.query("select from `reader` where `sid`='" + textBox9.Text + "'");
            }
            if (textBox14.Text != "")
            {
                db.query("select from `reader` where `name`='" + textBox14.Text + "'");
            }
            //循环读取
            while (db.fetchline())
            {
                string id = db.get("sid");
                //去找借的书的名字
                string booknames = "";
                DBcore.DBcore db2 = new DBcore.DBcore(".\\");
                db2.query("use DB");
                db2.query("select from `lendinfo` where `readerid`='" + id + "'");
                while (db2.fetchline())
                {
                    string bcd = db2.get("bookid");
                    DBcore.DBcore db3 = new DBcore.DBcore(".\\");
                    db3.query("use DB");
                    db3.query("select from `book` where `id`='" + bcd + "'");
                    while (db3.fetchline())
                    {
                        booknames = booknames +db3.get("booktitle") +"||";
                    }
                }
                string booktitle = db.get("name");
                string description = db.get("sex");
                string writer = db.get("lending");
                string publisher = db.get("maxnum");
                string type = db.get("owe");
                DataGridViewRow row = new DataGridViewRow();
                row.CreateCells(readerresult);
                row.Cells[0].Value = id;
                row.Cells[1].Value = booktitle;
                row.Cells[2].Value = description;
                row.Cells[3].Value = writer;
                row.Cells[4].Value = publisher;
                row.Cells[5].Value = type;
                row.Cells[6].Value = booknames;
                //添加新行
                readerresult.Rows.Add(row);
            }
            readerresult.Visible = true;
        }
        //限制输入数字
        void onlynums(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar < 59 && e.KeyChar > 47 || e.KeyChar == 8)
            {
                e.Handled = false;
            }
            else
            {
                e.Handled = true;
            }
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            onlynums(sender, e);
        }
        private void textBox9_KeyPress(object sender, KeyPressEventArgs e)
        {
            onlynums(sender, e);
        }

        private void textBox5_KeyPress(object sender, KeyPressEventArgs e)
        {
            onlynums(sender, e);
        }

        private void textBox7_KeyPress(object sender, KeyPressEventArgs e)
        {
            onlynums(sender, e);
        }

        private void textBox13_KeyPress(object sender, KeyPressEventArgs e)
        {
            onlynums(sender, e);
        }
        private void textBox8_KeyPress(object sender, KeyPressEventArgs e)
        {
            onlynums(sender, e);
        }

        private void new_bookid_KeyPress(object sender, KeyPressEventArgs e)
        {
            onlynums(sender, e);
        }

        private void new_nums_KeyPress(object sender, KeyPressEventArgs e)
        {
            onlynums(sender, e);
        }
        private void textBox4_KeyPress(object sender, KeyPressEventArgs e)
        {
            onlynums(sender, e);
        }

        private void textBox17_KeyPress(object sender, KeyPressEventArgs e)
        {
            onlynums(sender, e);
        }

        private void textBox16_KeyPress(object sender, KeyPressEventArgs e)
        {
            onlynums(sender, e);
        }


    }
}
