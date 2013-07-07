using System;
using System.Collections.Generic;
using System.Text;
using System.IO;


namespace Readfile
{
    public class Readfile
    {
        public string GetConfig(string path,string name)
        {
            StreamReader sr = new StreamReader(path);
            //初始化数组
            string[] config = "1=1".ToString().Split('=');
            //循环读取所需设置
            int r = 0;
            while (config[0] != name && sr.EndOfStream==false||r>=10 )
            {
                config = sr.ReadLine().ToString().Split('=');
                r++;
            }
            sr.Close();
            try
            {
                return config[1];
            }

            catch
            {
                return "";
            
            }
        }

        public bool SetPwd(string path,string username,string userpwd)
        {
            FileStream sm = new FileStream(path, FileMode.Create);
            StreamWriter sw = new StreamWriter(sm);
            sw.Write("[管理员信息]");
            sw.Write("\r\n");
            sw.Write("\r\n");
            sw.Write("-------请勿改动以下内容------");
            sw.Write("\r\n");
            sw.Write("username="+username);
            sw.Write("\r\n");
            sw.Write("userpassword="+userpwd);
            sw.Write("\r\n");
            sw.Write("-------请勿改动以上内容------");
            sw.Close();
            sm.Close();
            return true;

        }


        //历史记录加入
        public void AddDetail(string path, string detail)
        {
            //如果文件不存在则新建

            FileStream File = new FileStream(path, FileMode.OpenOrCreate);
            //如果是新建的文件。。。则写入meta属性
            if (File.Length == 0)
            {

                StreamWriter sw1 = new StreamWriter(File);

                sw1.Write("<html><head><meta http-equiv=content-type content=\"text/html; charset=UTF-8\"></head><body>");

                sw1.Close();
            }

            File.Close();

            FileStream append = new FileStream(path, FileMode.Append);

            StreamWriter sw = new StreamWriter(append);

            sw.Write(detail);
            //写入换行符
            sw.Write("<br />");

            sw.Close();


        }
        public bool Existen(string path)
        {
            try
            {
                FileStream File = new FileStream(path, FileMode.Open);
                File.Close();
                return true;
            }
            catch
            {
                return false;
            }
        }

    }
}
