using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SlimDX.Windows;

namespace SG
{
    public class SG
    {
        public static Form MainWindow;
        public static SlimDX.Direct3D11.Device DirectDevice;
        public static SlimDX.DXGI.SwapChain DirectSwapChain;
        public static SlimDX.Direct3D11.DeviceContext DirectContext;
        public static SlimDX.Direct3D11.Viewport DirectViewport;
        public static SlimDX.Direct3D11.RenderTargetView DirectRenderTarget;
        public static Graphics Graphics2D;

        public static void SetupDX()
        {
            MainWindow = new RenderForm("SG");

            // Setup Direct3D Device and Swapchain
            var description = new SlimDX.DXGI.SwapChainDescription()
            {
                BufferCount = 1,
                Usage = SlimDX.DXGI.Usage.RenderTargetOutput,
                OutputHandle = MainWindow.Handle,
                IsWindowed = true,
                ModeDescription = new SlimDX.DXGI.ModeDescription(0, 0, new SlimDX.Rational(60, 1), SlimDX.DXGI.Format.R8G8B8A8_UNorm),
                SampleDescription = new SlimDX.DXGI.SampleDescription(1, 0),
                Flags = SlimDX.DXGI.SwapChainFlags.AllowModeSwitch,
                SwapEffect = SlimDX.DXGI.SwapEffect.Discard
            };

            SlimDX.Direct3D11.Device.CreateWithSwapChain(SlimDX.Direct3D11.DriverType.Hardware, SlimDX.Direct3D11.DeviceCreationFlags.None,
                description, out DirectDevice, out DirectSwapChain);

            DirectContext = DirectDevice.ImmediateContext;

            // Handle Alt-Enter Functionality
            using (var factory = DirectSwapChain.GetParent<SlimDX.DXGI.Factory>())
            {
                factory.SetWindowAssociation(MainWindow.Handle, SlimDX.DXGI.WindowAssociationFlags.IgnoreAltEnter);
            }

            MainWindow.KeyDown += (o, e) =>
            {
                if (e.Alt && e.KeyCode == Keys.Enter)
                    DirectSwapChain.IsFullScreen = !DirectSwapChain.IsFullScreen;
            };

            // Create Viewport
            DirectViewport = new SlimDX.Direct3D11.Viewport(0.0f, 0.0f, MainWindow.ClientSize.Width, MainWindow.ClientSize.Height);
            DirectContext.Rasterizer.SetViewports(DirectViewport);

            // Create RenderTarget
            using (var resource = SlimDX.Direct3D11.Resource.FromSwapChain<SlimDX.Direct3D11.Texture2D>(DirectSwapChain, 0))
            {
                DirectRenderTarget = new SlimDX.Direct3D11.RenderTargetView(DirectDevice, resource);
            }

            DirectContext.OutputMerger.SetTargets(DirectRenderTarget);

            Graphics2D = new Graphics();
        }

        public static void CleanUpDX()
        {
            DirectDevice.Dispose();
            DirectSwapChain.Dispose();
            DirectContext.Dispose();
            DirectRenderTarget.Dispose();
            Graphics2D.Dispose();
        }

        public static void Update()
        {
            DirectContext.ClearRenderTargetView(DirectRenderTarget, new SlimDX.Color4(0.5f, 0.5f, 1.0f));
            DirectSwapChain.Present(0, SlimDX.DXGI.PresentFlags.None);
        }

        [STAThread]
        public static void Main()
        {
            SetupDX();
            MessagePump.Run(MainWindow, Update);
            CleanUpDX();
            
            /*
            GameState.AddItem(new Potion(), 5);
            GameState.AddItem(new Rock(), 3);
            GameState.AddEnemy(new Rat());
            GameState.AddEnemy(new Rat());
            WordHandler.AddWord(new Strength());

            while (GameState.Running())
            {
                GameState.TakeTurn();
                GameState.ClearDefeated();
            }
            */
        }
    }
}
