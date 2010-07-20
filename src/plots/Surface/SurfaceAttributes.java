// ***************************************************************************
//
// Copyright (c) 2000 - 2010, Lawrence Livermore National Security, LLC
// Produced at the Lawrence Livermore National Laboratory
// LLNL-CODE-442911
// All rights reserved.
//
// This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
// full copyright notice is contained in the file COPYRIGHT located at the root
// of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
//
// Redistribution  and  use  in  source  and  binary  forms,  with  or  without
// modification, are permitted provided that the following conditions are met:
//
//  - Redistributions of  source code must  retain the above  copyright notice,
//    this list of conditions and the disclaimer below.
//  - Redistributions in binary form must reproduce the above copyright notice,
//    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
//    documentation and/or other materials provided with the distribution.
//  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
//    be used to endorse or promote products derived from this software without
//    specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
// ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
// LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
// DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
// SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
// CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
// LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
// OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ***************************************************************************

package llnl.visit.plots;

import llnl.visit.AttributeSubject;
import llnl.visit.CommunicationBuffer;
import llnl.visit.Plugin;
import llnl.visit.ColorAttribute;

// ****************************************************************************
// Class: SurfaceAttributes
//
// Purpose:
//    Attributes for the surface plot
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class SurfaceAttributes extends AttributeSubject implements Plugin
{
    private static int numAdditionalAttributes = 17;

    // Enum values
    public final static int COLORBYTYPE_CONSTANT = 0;
    public final static int COLORBYTYPE_ZVALUE = 1;

    public final static int SCALING_LINEAR = 0;
    public final static int SCALING_LOG = 1;
    public final static int SCALING_SKEW = 2;

    public final static int LIMITSMODE_ORIGINALDATA = 0;
    public final static int LIMITSMODE_CURRENTPLOT = 1;


    public SurfaceAttributes()
    {
        super(numAdditionalAttributes);

        legendFlag = true;
        lightingFlag = true;
        surfaceFlag = true;
        wireframeFlag = false;
        limitsMode = LIMITSMODE_ORIGINALDATA;
        minFlag = false;
        maxFlag = false;
        colorByZFlag = true;
        scaling = SCALING_LINEAR;
        lineStyle = 0;
        lineWidth = 0;
        surfaceColor = new ColorAttribute(0, 0, 0);
        wireframeColor = new ColorAttribute(0, 0, 0);
        skewFactor = 1;
        min = 0;
        max = 1;
        colorTableName = new String("hot");
    }

    public SurfaceAttributes(int nMoreFields)
    {
        super(numAdditionalAttributes + nMoreFields);

        legendFlag = true;
        lightingFlag = true;
        surfaceFlag = true;
        wireframeFlag = false;
        limitsMode = LIMITSMODE_ORIGINALDATA;
        minFlag = false;
        maxFlag = false;
        colorByZFlag = true;
        scaling = SCALING_LINEAR;
        lineStyle = 0;
        lineWidth = 0;
        surfaceColor = new ColorAttribute(0, 0, 0);
        wireframeColor = new ColorAttribute(0, 0, 0);
        skewFactor = 1;
        min = 0;
        max = 1;
        colorTableName = new String("hot");
    }

    public SurfaceAttributes(SurfaceAttributes obj)
    {
        super(numAdditionalAttributes);

        legendFlag = obj.legendFlag;
        lightingFlag = obj.lightingFlag;
        surfaceFlag = obj.surfaceFlag;
        wireframeFlag = obj.wireframeFlag;
        limitsMode = obj.limitsMode;
        minFlag = obj.minFlag;
        maxFlag = obj.maxFlag;
        colorByZFlag = obj.colorByZFlag;
        scaling = obj.scaling;
        lineStyle = obj.lineStyle;
        lineWidth = obj.lineWidth;
        surfaceColor = new ColorAttribute(obj.surfaceColor);
        wireframeColor = new ColorAttribute(obj.wireframeColor);
        skewFactor = obj.skewFactor;
        min = obj.min;
        max = obj.max;
        colorTableName = new String(obj.colorTableName);

        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return numAdditionalAttributes;
    }

    public boolean equals(SurfaceAttributes obj)
    {
        // Create the return value
        return ((legendFlag == obj.legendFlag) &&
                (lightingFlag == obj.lightingFlag) &&
                (surfaceFlag == obj.surfaceFlag) &&
                (wireframeFlag == obj.wireframeFlag) &&
                (limitsMode == obj.limitsMode) &&
                (minFlag == obj.minFlag) &&
                (maxFlag == obj.maxFlag) &&
                (colorByZFlag == obj.colorByZFlag) &&
                (scaling == obj.scaling) &&
                (lineStyle == obj.lineStyle) &&
                (lineWidth == obj.lineWidth) &&
                (surfaceColor == obj.surfaceColor) &&
                (wireframeColor == obj.wireframeColor) &&
                (skewFactor == obj.skewFactor) &&
                (min == obj.min) &&
                (max == obj.max) &&
                (colorTableName.equals(obj.colorTableName)));
    }

    public String GetName() { return "Surface"; }
    public String GetVersion() { return "1.0"; }

    // Property setting methods
    public void SetLegendFlag(boolean legendFlag_)
    {
        legendFlag = legendFlag_;
        Select(0);
    }

    public void SetLightingFlag(boolean lightingFlag_)
    {
        lightingFlag = lightingFlag_;
        Select(1);
    }

    public void SetSurfaceFlag(boolean surfaceFlag_)
    {
        surfaceFlag = surfaceFlag_;
        Select(2);
    }

    public void SetWireframeFlag(boolean wireframeFlag_)
    {
        wireframeFlag = wireframeFlag_;
        Select(3);
    }

    public void SetLimitsMode(int limitsMode_)
    {
        limitsMode = limitsMode_;
        Select(4);
    }

    public void SetMinFlag(boolean minFlag_)
    {
        minFlag = minFlag_;
        Select(5);
    }

    public void SetMaxFlag(boolean maxFlag_)
    {
        maxFlag = maxFlag_;
        Select(6);
    }

    public void SetColorByZFlag(boolean colorByZFlag_)
    {
        colorByZFlag = colorByZFlag_;
        Select(7);
    }

    public void SetScaling(int scaling_)
    {
        scaling = scaling_;
        Select(8);
    }

    public void SetLineStyle(int lineStyle_)
    {
        lineStyle = lineStyle_;
        Select(9);
    }

    public void SetLineWidth(int lineWidth_)
    {
        lineWidth = lineWidth_;
        Select(10);
    }

    public void SetSurfaceColor(ColorAttribute surfaceColor_)
    {
        surfaceColor = surfaceColor_;
        Select(11);
    }

    public void SetWireframeColor(ColorAttribute wireframeColor_)
    {
        wireframeColor = wireframeColor_;
        Select(12);
    }

    public void SetSkewFactor(double skewFactor_)
    {
        skewFactor = skewFactor_;
        Select(13);
    }

    public void SetMin(double min_)
    {
        min = min_;
        Select(14);
    }

    public void SetMax(double max_)
    {
        max = max_;
        Select(15);
    }

    public void SetColorTableName(String colorTableName_)
    {
        colorTableName = colorTableName_;
        Select(16);
    }

    // Property getting methods
    public boolean        GetLegendFlag() { return legendFlag; }
    public boolean        GetLightingFlag() { return lightingFlag; }
    public boolean        GetSurfaceFlag() { return surfaceFlag; }
    public boolean        GetWireframeFlag() { return wireframeFlag; }
    public int            GetLimitsMode() { return limitsMode; }
    public boolean        GetMinFlag() { return minFlag; }
    public boolean        GetMaxFlag() { return maxFlag; }
    public boolean        GetColorByZFlag() { return colorByZFlag; }
    public int            GetScaling() { return scaling; }
    public int            GetLineStyle() { return lineStyle; }
    public int            GetLineWidth() { return lineWidth; }
    public ColorAttribute GetSurfaceColor() { return surfaceColor; }
    public ColorAttribute GetWireframeColor() { return wireframeColor; }
    public double         GetSkewFactor() { return skewFactor; }
    public double         GetMin() { return min; }
    public double         GetMax() { return max; }
    public String         GetColorTableName() { return colorTableName; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteBool(legendFlag);
        if(WriteSelect(1, buf))
            buf.WriteBool(lightingFlag);
        if(WriteSelect(2, buf))
            buf.WriteBool(surfaceFlag);
        if(WriteSelect(3, buf))
            buf.WriteBool(wireframeFlag);
        if(WriteSelect(4, buf))
            buf.WriteInt(limitsMode);
        if(WriteSelect(5, buf))
            buf.WriteBool(minFlag);
        if(WriteSelect(6, buf))
            buf.WriteBool(maxFlag);
        if(WriteSelect(7, buf))
            buf.WriteBool(colorByZFlag);
        if(WriteSelect(8, buf))
            buf.WriteInt(scaling);
        if(WriteSelect(9, buf))
            buf.WriteInt(lineStyle);
        if(WriteSelect(10, buf))
            buf.WriteInt(lineWidth);
        if(WriteSelect(11, buf))
            surfaceColor.Write(buf);
        if(WriteSelect(12, buf))
            wireframeColor.Write(buf);
        if(WriteSelect(13, buf))
            buf.WriteDouble(skewFactor);
        if(WriteSelect(14, buf))
            buf.WriteDouble(min);
        if(WriteSelect(15, buf))
            buf.WriteDouble(max);
        if(WriteSelect(16, buf))
            buf.WriteString(colorTableName);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetLegendFlag(buf.ReadBool());
            break;
        case 1:
            SetLightingFlag(buf.ReadBool());
            break;
        case 2:
            SetSurfaceFlag(buf.ReadBool());
            break;
        case 3:
            SetWireframeFlag(buf.ReadBool());
            break;
        case 4:
            SetLimitsMode(buf.ReadInt());
            break;
        case 5:
            SetMinFlag(buf.ReadBool());
            break;
        case 6:
            SetMaxFlag(buf.ReadBool());
            break;
        case 7:
            SetColorByZFlag(buf.ReadBool());
            break;
        case 8:
            SetScaling(buf.ReadInt());
            break;
        case 9:
            SetLineStyle(buf.ReadInt());
            break;
        case 10:
            SetLineWidth(buf.ReadInt());
            break;
        case 11:
            surfaceColor.Read(buf);
            Select(11);
            break;
        case 12:
            wireframeColor.Read(buf);
            Select(12);
            break;
        case 13:
            SetSkewFactor(buf.ReadDouble());
            break;
        case 14:
            SetMin(buf.ReadDouble());
            break;
        case 15:
            SetMax(buf.ReadDouble());
            break;
        case 16:
            SetColorTableName(buf.ReadString());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + boolToString("legendFlag", legendFlag, indent) + "\n";
        str = str + boolToString("lightingFlag", lightingFlag, indent) + "\n";
        str = str + boolToString("surfaceFlag", surfaceFlag, indent) + "\n";
        str = str + boolToString("wireframeFlag", wireframeFlag, indent) + "\n";
        str = str + indent + "limitsMode = ";
        if(limitsMode == LIMITSMODE_ORIGINALDATA)
            str = str + "LIMITSMODE_ORIGINALDATA";
        if(limitsMode == LIMITSMODE_CURRENTPLOT)
            str = str + "LIMITSMODE_CURRENTPLOT";
        str = str + "\n";
        str = str + boolToString("minFlag", minFlag, indent) + "\n";
        str = str + boolToString("maxFlag", maxFlag, indent) + "\n";
        str = str + boolToString("colorByZFlag", colorByZFlag, indent) + "\n";
        str = str + indent + "scaling = ";
        if(scaling == SCALING_LINEAR)
            str = str + "SCALING_LINEAR";
        if(scaling == SCALING_LOG)
            str = str + "SCALING_LOG";
        if(scaling == SCALING_SKEW)
            str = str + "SCALING_SKEW";
        str = str + "\n";
        str = str + intToString("lineStyle", lineStyle, indent) + "\n";
        str = str + intToString("lineWidth", lineWidth, indent) + "\n";
        str = str + indent + "surfaceColor = {" + surfaceColor.Red() + ", " + surfaceColor.Green() + ", " + surfaceColor.Blue() + ", " + surfaceColor.Alpha() + "}\n";
        str = str + indent + "wireframeColor = {" + wireframeColor.Red() + ", " + wireframeColor.Green() + ", " + wireframeColor.Blue() + ", " + wireframeColor.Alpha() + "}\n";
        str = str + doubleToString("skewFactor", skewFactor, indent) + "\n";
        str = str + doubleToString("min", min, indent) + "\n";
        str = str + doubleToString("max", max, indent) + "\n";
        str = str + stringToString("colorTableName", colorTableName, indent) + "\n";
        return str;
    }


    // Attributes
    private boolean        legendFlag;
    private boolean        lightingFlag;
    private boolean        surfaceFlag;
    private boolean        wireframeFlag;
    private int            limitsMode;
    private boolean        minFlag;
    private boolean        maxFlag;
    private boolean        colorByZFlag;
    private int            scaling;
    private int            lineStyle;
    private int            lineWidth;
    private ColorAttribute surfaceColor;
    private ColorAttribute wireframeColor;
    private double         skewFactor;
    private double         min;
    private double         max;
    private String         colorTableName;
}

