﻿using System;
using System.Runtime.InteropServices;
using System.Text;

namespace UniversalSplitScreen.SendInput
{
	static class WinApi
	{
		/// <summary>
		/// Places (posts) a message in the message queue associated with the thread that created the specified window and returns without waiting for the thread to process the message.
		/// </summary>
		/// <param name="hWnd"></param>
		/// <param name="Msg"></param>
		/// <param name="wParam"></param>
		/// <param name="lParam"></param>
		/// <returns></returns>
		[return: MarshalAs(UnmanagedType.Bool)]
		[DllImport("User32.dll", CharSet = CharSet.Auto)]
		public static extern bool PostMessageA(HandleRef hWnd, uint Msg, IntPtr wParam, IntPtr lParam);

		[return: MarshalAs(UnmanagedType.Bool)]
		[DllImport("User32.dll", CharSet = CharSet.Auto)]
		public static extern bool PostMessageA(HandleRef hWnd, uint Msg, IntPtr wParam, UIntPtr lParam);

		/// <summary>
		/// Places (posts) a message in the message queue associated with the thread that created the specified window and returns without waiting for the thread to process the message.
		/// </summary>
		/// <param name="hWnd"></param>
		/// <param name="Msg"></param>
		/// <param name="wParam"></param>
		/// <param name="lParam"></param>
		/// <returns></returns>
		/*public static bool PostMessageA(IntPtr hWnd, uint Msg, IntPtr wParam, IntPtr lParam)
		{
			var obj = new object();
			var handleRef = new HandleRef(obj, hWnd);
			bool result = PostMessageA(handleRef, Msg, wParam, lParam);
			GC.KeepAlive(obj);
			return result;
		}*/

		[return: MarshalAs(UnmanagedType.Bool)]
		[DllImport("User32.dll", CharSet = CharSet.Auto)]
		public static extern bool PostMessageA(IntPtr hWnd, uint Msg, IntPtr wParam, IntPtr lParam);

		/// <summary>
		/// Places (posts) a message in the message queue associated with the thread that created the specified window and returns without waiting for the thread to process the message.
		/// </summary>
		/// <param name="hWnd"></param>
		/// <param name="Msg"></param>
		/// <param name="wParam"></param>
		/// <param name="lParam"></param>
		/// <returns></returns>
		public static bool PostMessageA(IntPtr hWnd, uint Msg, IntPtr wParam, UIntPtr lParam)
		{
			var obj = new object();
			var handleRef = new HandleRef(obj, hWnd);
			bool result = PostMessageA(handleRef, Msg, wParam, lParam);
			GC.KeepAlive(obj);
			return result;
		}


		[DllImport("user32.dll", CharSet = CharSet.Auto)]
		public static extern IntPtr SendMessage(IntPtr hWnd, int Msg, IntPtr wParam, StringBuilder lParam);

		[DllImport("user32.dll", CharSet = CharSet.Auto)]
		public static extern IntPtr SendMessage(IntPtr hWnd, int Msg, IntPtr wParam, [MarshalAs(UnmanagedType.LPWStr)] string lParam);

		[DllImport("user32.dll", CharSet = CharSet.Auto)]
		public static extern IntPtr SendMessage(IntPtr hWnd, int Msg, int wParam, [MarshalAs(UnmanagedType.LPWStr)] string lParam);

		[DllImport("user32.dll", CharSet = CharSet.Auto)]
		public static extern IntPtr SendMessage(IntPtr hWnd, int Msg, int wParam, ref IntPtr lParam);

		/// <summary>
		/// Sends the specified message to a window or windows. The SendMessage function calls the window procedure for the specified window and does not return until the window procedure has processed the message.
		/// </summary>
		/// <param name="hWnd"></param>
		/// <param name="Msg"></param>
		/// <param name="wParam"></param>
		/// <param name="lParam"></param>
		/// <returns></returns>
		[DllImport("user32.dll", CharSet = CharSet.Auto)]
		public static extern IntPtr SendMessage(IntPtr hWnd, int Msg, int wParam, IntPtr lParam);

		/// <summary>
		/// Sends the specified message to a window or windows. 
		/// If the window was created by the calling thread, SendNotifyMessage calls the window procedure for the window and does not return until the window procedure has processed the message. 
		/// If the window was created by a different thread, SendNotifyMessage passes the message to the window procedure and returns immediately; it does not wait for the window procedure to finish processing the message.
		/// </summary>
		/// <param name="hWnd"></param>
		/// <param name="Msg"></param>
		/// <param name="wParam"></param>
		/// <param name="lParam"></param>
		/// <returns></returns>
		[DllImport("user32.dll", CharSet = CharSet.Auto)]
		public static extern bool SendNotifyMessage(IntPtr hWnd, uint Msg, UIntPtr wParam, IntPtr lParam);

		//https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-setcapture
		[DllImport("user32.dll")]
		public static extern IntPtr SetCapture(IntPtr hWnd);

		[DllImport("user32.dll")]
		[return: MarshalAs(UnmanagedType.Bool)]
		public static extern bool SetForegroundWindow(IntPtr hWnd);

		[DllImport("user32.dll")]
		public static extern bool BlockInput(bool fBlockIt);
	}
}
