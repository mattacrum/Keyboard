re#include "SequenceCapture.h"
#include "Visualizer.h"
#include "LandmarkDetectorFunc.h"
#include "GazeEstimation.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>
#include <cmath>
#include <unistd.h>

#define ADDRESS "servsock"

using namespace std;

cv::Point3d getMidPoint(cv::Point3d left_corner, cv::Point3d right_corner, cv::Point3d midpoint)
{
	midpoint.x = midpoint.x + (right_corner.x + left_corner.x)/2;
	midpoint.y = midpoint.y + (right_corner.y + left_corner.y)/2;
	midpoint.z = midpoint.z + (right_corner.z + left_corner.z)/2;

	return midpoint;
}

void resetPoints(cv::Point3d &avgValue, cv::Point3d &midpoint, cv::Vec2d &avgGazeAngle, cv::Point3f &avgGazeVector)
{
	avgValue.x = 0;
	avgValue.y = 0;
	avgValue.z = 0;
	midpoint.x = 0;
	midpoint.y = 0;
	midpoint.z = 0;
	avgGazeVector.x = 0;
	avgGazeVector.y = 0;
	avgGazeVector.z = 0;
	avgGazeAngle[0] = 0;
	avgGazeAngle[1] = 0;	
}


int main()
{
	
	Utilities::SequenceCapture video;
	Utilities::Visualizer visualizer(true, false, false, false);
	LandmarkDetector::FaceModelParameters det_parameters;
	LandmarkDetector::CLNF face_model(det_parameters.model_location);
	int counter = 0;
	cv::Point3d avgValue(0, 0, 0);
	cv::Point3d midpoint(0, 0, 0);
	cv::Vec2d avgGazeAngle(0, 0);
	cv::Point3f avgGazeVector(0, 0, 0);


	int server_fd, new_socket, len, bytes;
	unsigned int valread;
	struct sockaddr_un address, saun;

	if((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
	{
		perror("socket unable to be established");
		exit(1);
	}
 
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, ADDRESS);

	unlink(ADDRESS);
	len = sizeof(address.sun_family) + strlen(address.sun_path);

	if(bind(server_fd, (sockaddr*)&address, len) < 0)
	{
		perror("unable to bind to socket");
		exit(1);
	}

	if(listen(server_fd, 5) < 0)
	{
		perror("unable to listen to socket");
		exit(1);
	}

	if((new_socket = accept(server_fd, (sockaddr*)&saun, &valread)) < 0)
	{
		perror("unable to accept");
		exit(1);
	}
	
	


	if(video.OpenWebcam(0))
	{
		cout << "Open" << endl;
		while(video.IsOpened())
		{
			vector<cv::Point3f> eye_landmarks;
			cv::Mat frame = video.GetNextFrame();
			cv::Mat_<uchar> frame_gray = video.GetGrayFrame();

			bool success = LandmarkDetector::DetectLandmarksInVideo(frame, face_model, det_parameters, frame_gray);

			cv::Point3f gazeDirection0(0, 0, 0);
			cv::Point3f gazeDirection1(0, 0, 0);
			cv::Vec2d gazeAngle(0, 0);

			if(success)
			{
				counter++;
				
				GazeAnalysis::EstimateGaze(face_model, gazeDirection0, video.fx, video.fy, video.cx, video.cy, true);
				GazeAnalysis::EstimateGaze(face_model, gazeDirection1, video.fx, video.fy, video.cx, video.cy, false);
				gazeAngle = GazeAnalysis::GetGazeAngle(gazeDirection0, gazeDirection1);
				
				eye_landmarks = LandmarkDetector::Calculate3DEyeLandmarks(face_model, video.fx, video.fy, video.cx, video.cy);
	
				//midpoint = getMidPoint(eye_landmarks[14], eye_landmarks[36], midpoint);
				
				//avgGazeAngle[0] += gazeAngle[0];
				//avgGazeAngle[1] += gazeAngle[1];

				avgGazeVector += gazeDirection0;
				

				if(counter == 5)
				{
					counter = 0;
					
					//avgValue.x = midpoint.x / 10;
					//avgValue.y = midpoint.y / 10;
					//avgValue.z = midpoint.z / 10;
					//avgGazeAngle[0] /= 10;
					//avgGazeAngle[1] /= 10;
					avgGazeVector /= 5;
					
					//cout << avgValue.x << " " << avgValue.y << " " << avgValue.z << endl;
					//cout << avgGazeAngle[0] << " " << avgGazeAngle[1] << endl;

					cout << avgGazeVector.x << " " << avgGazeVector.y << " " << avgGazeVector.z << endl;

					bytes = send(new_socket, &avgGazeVector, sizeof(avgGazeVector), 0);		

					resetPoints(avgValue, midpoint, avgGazeAngle, avgGazeVector);
					
					
				}
			}
	
			
			visualizer.SetImage(frame, video.fx, video.fy, video.cx, video.cy);
			visualizer.SetObservationGaze(gazeDirection0, gazeDirection1, LandmarkDetector::CalculateAllEyeLandmarks(face_model), LandmarkDetector::Calculate3DEyeLandmarks(face_model, video.fx, video.fy, video.cx, video.cy), face_model.detection_certainty);
			
			char c = visualizer.ShowObservation();

			
			if(c == 27)
			{
				break;
			}
		}
	}

	video.Close();
	close(server_fd);	
	
	return 0;

}
