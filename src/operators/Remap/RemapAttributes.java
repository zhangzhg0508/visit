// ***************************************************************************
//
// Copyright (c) 2000 - 2018, Lawrence Livermore National Security, LLC
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

package llnl.visit.operators;

import llnl.visit.AttributeSubject;
import llnl.visit.CommunicationBuffer;
import llnl.visit.Plugin;

// ****************************************************************************
// Class: RemapAttributes
//
// Purpose:
//    Atts for Remap operator
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class RemapAttributes extends AttributeSubject implements Plugin
{
    private static int RemapAttributes_numAdditionalAtts = 9;

    // Enum values
    public final static int VARIABLETYPES_INTRINSIC = 0;
    public final static int VARIABLETYPES_EXTRINSIC = 1;


    public RemapAttributes()
    {
        super(RemapAttributes_numAdditionalAtts);

        useExtents = true;
        startX = 0;
        endX = 1;
        cellsX = 10;
        startY = 0;
        endY = 1;
        cellsY = 10;
        defaultValue = 0;
        variableType = VARIABLETYPES_INTRINSIC;
    }

    public RemapAttributes(int nMoreFields)
    {
        super(RemapAttributes_numAdditionalAtts + nMoreFields);

        useExtents = true;
        startX = 0;
        endX = 1;
        cellsX = 10;
        startY = 0;
        endY = 1;
        cellsY = 10;
        defaultValue = 0;
        variableType = VARIABLETYPES_INTRINSIC;
    }

    public RemapAttributes(RemapAttributes obj)
    {
        super(obj);

        useExtents = obj.useExtents;
        startX = obj.startX;
        endX = obj.endX;
        cellsX = obj.cellsX;
        startY = obj.startY;
        endY = obj.endY;
        cellsY = obj.cellsY;
        defaultValue = obj.defaultValue;
        variableType = obj.variableType;

        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return RemapAttributes_numAdditionalAtts;
    }

    public boolean equals(RemapAttributes obj)
    {
        // Create the return value
        return ((useExtents == obj.useExtents) &&
                (startX == obj.startX) &&
                (endX == obj.endX) &&
                (cellsX == obj.cellsX) &&
                (startY == obj.startY) &&
                (endY == obj.endY) &&
                (cellsY == obj.cellsY) &&
                (defaultValue == obj.defaultValue) &&
                (variableType == obj.variableType));
    }

    public String GetName() { return "Remap"; }
    public String GetVersion() { return "1.0"; }

    // Property setting methods
    public void SetUseExtents(boolean useExtents_)
    {
        useExtents = useExtents_;
        Select(0);
    }

    public void SetStartX(double startX_)
    {
        startX = startX_;
        Select(1);
    }

    public void SetEndX(double endX_)
    {
        endX = endX_;
        Select(2);
    }

    public void SetCellsX(int cellsX_)
    {
        cellsX = cellsX_;
        Select(3);
    }

    public void SetStartY(double startY_)
    {
        startY = startY_;
        Select(4);
    }

    public void SetEndY(double endY_)
    {
        endY = endY_;
        Select(5);
    }

    public void SetCellsY(int cellsY_)
    {
        cellsY = cellsY_;
        Select(6);
    }

    public void SetDefaultValue(double defaultValue_)
    {
        defaultValue = defaultValue_;
        Select(7);
    }

    public void SetVariableType(int variableType_)
    {
        variableType = variableType_;
        Select(8);
    }

    // Property getting methods
    public boolean GetUseExtents() { return useExtents; }
    public double  GetStartX() { return startX; }
    public double  GetEndX() { return endX; }
    public int     GetCellsX() { return cellsX; }
    public double  GetStartY() { return startY; }
    public double  GetEndY() { return endY; }
    public int     GetCellsY() { return cellsY; }
    public double  GetDefaultValue() { return defaultValue; }
    public int     GetVariableType() { return variableType; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteBool(useExtents);
        if(WriteSelect(1, buf))
            buf.WriteDouble(startX);
        if(WriteSelect(2, buf))
            buf.WriteDouble(endX);
        if(WriteSelect(3, buf))
            buf.WriteInt(cellsX);
        if(WriteSelect(4, buf))
            buf.WriteDouble(startY);
        if(WriteSelect(5, buf))
            buf.WriteDouble(endY);
        if(WriteSelect(6, buf))
            buf.WriteInt(cellsY);
        if(WriteSelect(7, buf))
            buf.WriteDouble(defaultValue);
        if(WriteSelect(8, buf))
            buf.WriteInt(variableType);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetUseExtents(buf.ReadBool());
            break;
        case 1:
            SetStartX(buf.ReadDouble());
            break;
        case 2:
            SetEndX(buf.ReadDouble());
            break;
        case 3:
            SetCellsX(buf.ReadInt());
            break;
        case 4:
            SetStartY(buf.ReadDouble());
            break;
        case 5:
            SetEndY(buf.ReadDouble());
            break;
        case 6:
            SetCellsY(buf.ReadInt());
            break;
        case 7:
            SetDefaultValue(buf.ReadDouble());
            break;
        case 8:
            SetVariableType(buf.ReadInt());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + boolToString("useExtents", useExtents, indent) + "\n";
        str = str + doubleToString("startX", startX, indent) + "\n";
        str = str + doubleToString("endX", endX, indent) + "\n";
        str = str + intToString("cellsX", cellsX, indent) + "\n";
        str = str + doubleToString("startY", startY, indent) + "\n";
        str = str + doubleToString("endY", endY, indent) + "\n";
        str = str + intToString("cellsY", cellsY, indent) + "\n";
        str = str + doubleToString("defaultValue", defaultValue, indent) + "\n";
        str = str + indent + "variableType = ";
        if(variableType == VARIABLETYPES_INTRINSIC)
            str = str + "VARIABLETYPES_INTRINSIC";
        if(variableType == VARIABLETYPES_EXTRINSIC)
            str = str + "VARIABLETYPES_EXTRINSIC";
        str = str + "\n";
        return str;
    }


    // Attributes
    private boolean useExtents;
    private double  startX;
    private double  endX;
    private int     cellsX;
    private double  startY;
    private double  endY;
    private int     cellsY;
    private double  defaultValue;
    private int     variableType;
}

