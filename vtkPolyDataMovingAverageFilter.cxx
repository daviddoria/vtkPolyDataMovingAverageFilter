#include "vtkPolyDataMovingAverageFilter.h"

#include "vtkDataObject.h"
#include "vtkIdList.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkKdTreePointLocator.h"
#include "vtkMath.h"
#include "vtkObjectFactory.h"
#include "vtkSmartPointer.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkVertexGlyphFilter.h"

vtkStandardNewMacro(vtkPolyDataMovingAverageFilter);

vtkPolyDataMovingAverageFilter::vtkPolyDataMovingAverageFilter()
{
  this->Radius = 1.0;
}

int vtkPolyDataMovingAverageFilter::RequestData(
    vtkInformation *vtkNotUsed(request),
    vtkInformationVector **inputVector,
    vtkInformationVector *outputVector)
{

  // Get the input and ouptut
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkPolyData* input = vtkPolyData::SafeDownCast(
    inInfo->Get(vtkDataObject::DATA_OBJECT()));

  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  vtkPolyData* output = vtkPolyData::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));

  //output->ShallowCopy(input);

  vtkSmartPointer<vtkPoints> newPoints =
    vtkSmartPointer<vtkPoints>::New();
  newPoints->SetNumberOfPoints(input->GetNumberOfPoints());

  vtkSmartPointer<vtkKdTreePointLocator> kdTree =
    vtkSmartPointer<vtkKdTreePointLocator>::New();
  kdTree->SetDataSet(input);
  kdTree->BuildLocator();

  for(vtkIdType pointId = 0; pointId < input->GetNumberOfPoints(); pointId++)
    {
    vtkSmartPointer<vtkIdList> neighborIds =
      vtkSmartPointer<vtkIdList>::New();

    double p[3];
    input->GetPoint(pointId,p);
    kdTree->FindPointsWithinRadius(this->Radius, p, neighborIds);
    //std::cout << "There are " << neighborIds->GetNumberOfIds() << " neighbors." << std::endl;
    vtkSmartPointer<vtkPoints> neighbors =
      vtkSmartPointer<vtkPoints>::New();
    for(vtkIdType neighborId = 0; neighborId < neighborIds->GetNumberOfIds(); neighborId++)
      {
      double neighbor[3];
      input->GetPoint(neighborIds->GetId(neighborId), neighbor);
      neighbors->InsertNextPoint(neighbor);
      }

    double center[3];
    CenterOfMass(neighbors,center);
    newPoints->SetPoint(pointId, center);
    }

  vtkSmartPointer<vtkPolyData> newPolydata =
    vtkSmartPointer<vtkPolyData>::New();
  newPolydata->SetPoints(newPoints);

  vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
  glyphFilter->SetInputConnection(newPolydata->GetProducerPort());
  glyphFilter->Update();

  output->ShallowCopy(glyphFilter->GetOutput());

  return 1;
}

void vtkPolyDataMovingAverageFilter::CenterOfMass(vtkPoints* points, double center[3])
{
  center[0] = 0.0;
  center[1] = 0.0;
  center[2] = 0.0;

  for(vtkIdType i = 0; i < points->GetNumberOfPoints(); i++)
    {
    double point[3];
    points->GetPoint(i, point);
    vtkMath::Add(center, point, center);
    }

  double numberOfPoints = static_cast<double>(points->GetNumberOfPoints());
  vtkMath::MultiplyScalar(center, 1./numberOfPoints);

}