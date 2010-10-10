/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPolyDataMovingAverageFilter.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkPolyDataMovingAverageFilter - Find the least squares plane through a set of points
// .SECTION Description
// vtkPolyDataMovingAverageFilter finds the least squares plane through a set of points.

#ifndef __vtkPolyDataMovingAverageFilter_h
#define __vtkPolyDataMovingAverageFilter_h

#include "vtkPolyDataAlgorithm.h"

class vtkPolyDataMovingAverageFilter : public vtkPolyDataAlgorithm
{
public:
  static vtkPolyDataMovingAverageFilter *New();
  vtkTypeMacro(vtkPolyDataMovingAverageFilter,vtkPolyDataAlgorithm);

  vtkPolyDataMovingAverageFilter();

  vtkSetMacro(Radius, double);

protected:

  void CenterOfMass(vtkPoints* points, double center[3]);



  int RequestData(vtkInformation* request,
                  vtkInformationVector** inputVector,
                  vtkInformationVector* outputVector );

  double Radius;

private:

  vtkPolyDataMovingAverageFilter(const vtkPolyDataMovingAverageFilter&);  // Not implemented.
  void operator=(const vtkPolyDataMovingAverageFilter&);  // Not implemented.
};

#endif
