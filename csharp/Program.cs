using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace Test
{
    class Program
    {
        /// <summary>
        /// DES加密解密函数。
        /// 该函数使用的是C++ dll中的导出函数，因此目录中必须存在与应用程序相同架构的NYEncryption.dll文件，否则报错。
        /// </summary>
        /// <param name="key">DES密码，必须是8个字节长度</param>
        /// <param name="inputFile">输入文件全名</param>
        /// <param name="outputFile">输出文件全名</param>
        /// <param name="isEncryption">是加密还是解密。true加密，false解密</param>
        /// <param name="isVerbose">是否显示输入。在控制台显示加密、解密信息、进度条等信息。全局开关，该参数线程不安全！！！</param>
        /// <returns>错误代码：
        /// 0:正常退出<br/>
        /// 1:文件名输入错误<br/>
        /// 2:key长度不是8字节<br/>
        /// -1:文件无法打开<br/>
        /// -2:要解密的文件不是要求的类型
        /// </returns>
        [DllImport("NYEncryption", EntryPoint = "yn_encrypt_decrypt")]
        public static extern int YNEncryptAndDecrypt(string key, string inputFile, string outputFile, bool isEncryption, bool isVerbose = false);

        static void Main(string[] args)
        {
            string key = "12345678";
            string inputFile = @"E:\pgAdmin3.7z";
            string outputFile = @"E:\pgAdmin3.7z.d";

            System.Console.WriteLine("Start Encryption...");
            int res = YNEncryptAndDecrypt(key, inputFile, outputFile, true); //加密，不输出任何信息
            System.Console.WriteLine("Done. Exit code:" + res);

            System.Console.WriteLine("Start Decryption(Verbose)...");
            res = YNEncryptAndDecrypt(key, outputFile, outputFile + ".7z", false, true); //解密，控制台输出详细信息
            System.Console.WriteLine("Done. Exit code:" + res);
        }
    }
}
