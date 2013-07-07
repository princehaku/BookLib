using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace BookLib
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();

            Application.SetCompatibleTextRenderingDefault(false);

            Launcher frm2 = new Launcher();
            //启动此窗口
            Application.Run(frm2);

            //Application.Run(new Form1());

        }
    }
}
