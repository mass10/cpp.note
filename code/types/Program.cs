using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace types
{
	internal sealed class Program
	{
		static void Main(string[] args)
		{
			dynamic型について();
		}

		private static void dynamic型について()
		{
			{
				// サジェストが機能する。普通の書き方。
				var c = new Class();
				c.Hello();
			}

			{
				// サジェストが機能せず、コンパイル時チェックも機能しない。
				dynamic c = new Class();
				c.Hello(); // 正しく呼び出される。
				c.Hello("bye"); // 正しく呼び出されない。実行時に例外を引き起こす。
				c.Bye(); // 何も呼び出されない。実行時に例外を引き起こす。
			}
		}
	}

	internal sealed class Class
	{
		public Class()
		{

		}

		public void Hello()
		{
			Console.WriteLine("[TRACE] Hello!");
		}
	}
}
