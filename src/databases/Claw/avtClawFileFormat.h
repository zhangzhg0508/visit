/*****************************************************************************
*
* Copyright (c) 2000 - 2010, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

// ************************************************************************* //
//                            avtClawFileFormat.h                           //
// ************************************************************************* //

#ifndef AVT_Claw_FILE_FORMAT_H
#define AVT_Claw_FILE_FORMAT_H

#include <avtMTMDFileFormat.h>

#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

struct TimeHeader_t
{
    double time;
    int meqn;
    int ngrids;
    int naux;
    int ndims;
};

struct GridHeader_t
{
    int grid_number;
    int AMR_level;
    int mx, my, mz;
    double xlow, ylow, zlow;
    double dx, dy, dz;
    int charsPerLine;
    int dataOffset;
};


// ****************************************************************************
//  Class: avtClawFileFormat
//
//  Purpose:
//      Reads in Claw files as a plugin to VisIt.
//
//  Programmer: miller -- generated by xml2avt
//  Creation:   Mon Sep 10 23:24:53 PST 2007
//
// ****************************************************************************

class avtClawFileFormat : public avtMTMDFileFormat
{
  public:
                           avtClawFileFormat(const char *);
    virtual               ~avtClawFileFormat() {;};

    bool                   HasInvariantMetaData(void) const { return false; };
    bool                   HasInvariantSIL(void) const { return false; };

    void                   BuildDomainAuxiliaryInfo(int timeState);

    virtual int            GetNTimesteps(void);
    virtual double         GetTime(int ts);

    virtual const char    *GetType(void)   { return "Claw"; };
    virtual void           FreeUpResources(void); 

    virtual vtkDataSet    *GetMesh(int, int, const char *);
    virtual vtkDataArray  *GetVar(int, int, const char *);
    virtual vtkDataArray  *GetVectorVar(int, int, const char *);

  protected:
    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *, int);
    void                   GetFilenames();

  private:
    string                 rootDir;
    string                 timeScanf;
    string                 gridScanf;
    string                 timeRegex;
    string                 gridRegex;
    string                 cycleRegex;
    string                 optMode;
    vector<string>         timeFilenames;
    vector<string>         gridFilenames;
    vector<TimeHeader_t>   timeHeaders;
    vector<vector<GridHeader_t> > gridHeaders;
    vector<map<int, GridHeader_t> > gridHeaderMaps;
};


#endif
