﻿using System;
using System.Threading.Tasks;
using System.Windows.Forms;
using UniversalSplitScreen.Core;
using UniversalSplitScreen.RawInput;
using UniversalSplitScreen.SendInput;
using UniversalSplitScreen.UI;

namespace UniversalSplitScreen
{
	class Program
	{
		public static Config Config { get; private set; }

		static Intercept i;

		public static Form1 Form { get; private set; }
		public static IntPtr Form_hWnd { get; private set; }
		public static SplitScreenManager SplitScreenManager { get; private set; }
		public static MessageProcessor MessageProcessor { get; private set; }
		public static OptionsStructure Options { get; private set; }

		[STAThread]
		static void Main(string[] args)
		{
			Config = Config.LoadConfig();
			if (Config?.AutomaticallyCheckForUpdatesOnStartup ?? true)
				UpdateChecker.CheckUpdateDialog(false);

			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);

			Form = new Form1();
			Form_hWnd = Form.Handle;
			Form.SetAutomaticallyCheckUpdatesChecked(Config?.AutomaticallyCheckForUpdatesOnStartup ?? true);
			
			Options = new OptionsStructure();

			Core.Options.LoadOptions();
			
			SplitScreenManager = new SplitScreenManager();
			SplitScreenManager.Init();

			MessageProcessor = new MessageProcessor();

			i = new Intercept();
			var x = new RawInputManager(Form_hWnd);

			//InputDisabler.Init();

			Application.Run(Form);//Not required for RegisterRawInputDevices to work

			SplitScreenManager.DeactivateSplitScreen();

			Logger.WriteLine("Exiting application");
			Environment.Exit(0);
		}
	}
}
