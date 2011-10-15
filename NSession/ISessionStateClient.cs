using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace NSession
{
    [ComVisible(true)]
    [Guid("A232ABCA-A611-4789-B338-3D43ABDD43BF")]
    //[InterfaceType(ComInterfaceType.InterfaceIsDual)]
    public interface ISessionStateClient
    {
        void GetItem();
        void GetItemExclusive();
        void SetAndReleaseItemExclusive();
    }
}
