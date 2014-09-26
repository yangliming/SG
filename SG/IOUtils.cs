using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SG
{
    public static class IOUtils
    {
        static IOUtils()
        {
//            Console.SetWindowSize(100, 40);
//            Console.SetCursorPosition(3, 0);
        }

        public static void WriteLine(string toWrite = null)
        {
            if (toWrite == null)
                System.Console.WriteLine();
            else
                System.Console.WriteLine(toWrite);
        }

        public static ConsoleKeyInfo ReadKey(bool intercept = true)
        {
            return System.Console.ReadKey(intercept);
        }

        public static void SetForegroundColor(ConsoleColor color)
        {
            Console.ForegroundColor = color;
        }

        public static void SetBackgroungColor(ConsoleColor color)
        {
            Console.BackgroundColor = color;
        }

        public static void ResetColor()
        {
            Console.ResetColor();
        }

        public static void Clear()
        {
            System.Console.Clear();
        }
    }
}
