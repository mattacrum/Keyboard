#include "SequenceCapture.h"
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

int main()
{
    char c;
    register int i, s, len;
	float x, y;	

    struct sockaddr_un saun;
	

    /*
     * Get a socket to work with.  This socket will
     * be in the UNIX domain, and will be a
     * stream socket.
     */
    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("client: socket");
        exit(1);
    }

    /*
     * Create the address we will be connecting to.
     */
    saun.sun_family = AF_UNIX;
    strcpy(saun.sun_path, ADDRESS);

    /*
     * Try to connect to the address.  For this to
     * succeed, the server must already have bound
     * this address, and must have issued a listen()
     * request.
     *
     * The third argument indicates the "length" of
     * the structure, not just the length of the
     * socket name.
     */
    len = sizeof(saun.sun_family) + strlen(saun.sun_path);

    if (connect(s, (sockaddr*)&saun, len) < 0) {
        perror("client: connect");
        exit(1);
    }

	int bytesRead = 0;
	bytesRead = read(s, &x, sizeof(x));

	bytesRead = read(s, &y, sizeof(y));

	std::cout << x << " " << y << std::endl;

    /*
     * We can simply use close() to terminate the
     * connection, since we're done with both sides.
     */
    close(s);

    exit(0);
}
