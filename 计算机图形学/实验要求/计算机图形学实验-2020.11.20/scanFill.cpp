//通用扫描线填充算法

#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define NULL 0
#define WINDOW_HEIGHT 400
#define WINDOW_WIDTH 400
struct dcPt {
	int x;
	int y;
};

typedef struct tEdge {
	int yUpper;
	float xIntersect, dxPerScan;
	struct tEdge * next;
} Edge;

void setPixel(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

/* Inserts edge into list in order of increasing xIntersect field. */
void insertEdge(Edge * list, Edge * edge) {
	Edge * p, * q = list;
	p = q->next;
	while(p != NULL) {
		if(edge->xIntersect < p->xIntersect)
			p = NULL;
		else {
			q = p;
			p = p->next;
		}
	}
	edge->next = q->next;
	q->next = edge;
}
/* For an index, return y-coordinate
 of next nonhorizontal line */
int yNext(int k, int cnt, dcPt * pts) {
	int j;
	if((k + 1) > (cnt - 1))
		j = 0;
	else
		j = k + 1;
	while(pts[k].y == pts[j].y)
		if((j + 1) > (cnt - 1))
			j = 0;
		else
			j++;
	return (pts[j].y);
}
/* Store lower-y coordinate and inverse slope for each edge.  Adjust and store upper-y coordinate for edges that are the lower member of a monotically increasing or decreasing pair of edges */
void makeEdgeRec
(dcPt lower, dcPt upper, int yComp, Edge * 	edge, Edge * edges[]) {
	edge->dxPerScan =
	    (float)(upper.x - lower.x) / (upper.y - lower.y);
	edge->xIntersect = lower.x;
	if(upper.y < yComp)
		edge->yUpper = upper.y - 1;
	else
		edge->yUpper = upper.y;
	insertEdge(edges[lower.y], edge);
}
void buildEdgeList(int cnt, dcPt * pts, Edge * edges[]) {
	Edge * edge;
	dcPt v1, v2;
	int i, yPrev = pts[cnt - 2].y;
	v1.x = pts[cnt - 1].x;
	v1.y = pts[cnt - 1].y;
	for(i = 0; i < cnt; i++) {
		v2 = pts[i];
		if(v1.y != v2.y) {                 /* nonhorizontal line */
			edge = (Edge *) malloc(sizeof(Edge));
			if(v1.y < v2.y)                  /* up-going edge      */
				makeEdgeRec(v1, v2, yNext(i, cnt, pts), edge, edges);
			else                             /* down-going edge    */
				makeEdgeRec(v2, v1, yPrev, edge, edges);
		}
		yPrev = v1.y;
		v1 = v2;
	}
}
void buildActiveList(int scan, Edge * active, Edge * edges[]) {
	Edge * p, * q;
	p = edges[scan]->next;
	while(p) {
		q = p->next;
		insertEdge(active, p);
		p = q;
	}
}
void fillScan(int scan, Edge * active) {
	Edge * p1, * p2;
	int i;
	p1 = active->next;
	while(p1) {
		p2 = p1->next;
		for(i = p1->xIntersect; i < p2->xIntersect; i++)
			setPixel((int) i, scan);
		p1 = p2->next;
	}
}
void deleteAfter(Edge * q) {
	Edge * p = q->next;
	q->next = p->next;
	free(p);
}

/* Delete completed edges. Update 'xIntersect' field for others */
void updateActiveList(int scan, Edge * active) {
	Edge * q = active, * p = active->next;
	while(p)
		if(scan >= p->yUpper) {
			p = p->next;
			deleteAfter(q);
		} else {
			p->xIntersect = p->xIntersect + p->dxPerScan;
			q = p;
			p = p->next;
		}
}
void resortActiveList(Edge * active) {
	Edge * q, * p = active->next;
	active->next = NULL;
	while(p) {
		q = p->next;
		insertEdge(active, p);
		p = q;
	}
}
void scanFill(int cnt, dcPt * pts) {
	Edge *edges[WINDOW_HEIGHT], * active;
	int i, scan;
	for(i = 0; i < WINDOW_HEIGHT; i++) {
		edges[i] = (Edge *) malloc(sizeof(Edge));
		edges[i]->next = NULL;
	}
	buildEdgeList(cnt, pts, edges);
	active = (Edge *) malloc(sizeof(Edge));
	active->next = NULL;
	for(scan = 0; scan < WINDOW_HEIGHT; scan++) {
		buildActiveList(scan, active, edges);
		if(active->next) {
			fillScan(scan, active);
			updateActiveList(scan, active);
			resortActiveList(active);
			Sleep(10); //停顿10毫秒，放慢填充速度，便于观看填充过程
		}
	}
	/* Free edge records that have been malloc'ed ... */
}
/*  以下注释代码为课件上的程序代码，改写为OpenGL实现的主函数
void main (int argc, char ** argv)
{

  dcPt pts[] = {
    WINDOW_WIDTH/4, WINDOW_HEIGHT/4,
    3*WINDOW_WIDTH/4, 3*WINDOW_HEIGHT/4,
    3*WINDOW_WIDTH/4, WINDOW_HEIGHT/4,
    WINDOW_WIDTH/4, 3*WINDOW_HEIGHT/4
    };

  long windowID = openGraphics (*argv, WINDOW_WIDTH, WINDOW_HEIGHT);

  setBackground (WHITE);
  setColor (BLACK);
  scanFill (4, pts);
  sleep (20);
  closeGraphics (windowID);
}
*/

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);   // Set display-window color to white.
	glMatrixMode(GL_PROJECTION);        // Set projection parameters.
	gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
}

void myDraw(void) {
	dcPt pts[] = {
		50, 50,
		300, 20,
		300, 300,
		200, 100,
		150, 350,
		20, 120
	};
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	scanFill(6, pts);  // 第一个参数为填充图元的顶点数，第二个参数为顶点坐标数组
	Sleep(20);
	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);                          // Initialize GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // Set display mode.
	glutInitWindowPosition(50, 100);    // Set top-left display-window position.
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);       // Set display-window width and height.
	glutCreateWindow("通用扫描线填充");  // Create display window.
	init();                              // Execute initialization procedure.
	glutDisplayFunc(myDraw);        // Send graphics to display window.
	glutMainLoop();                      // Display everything and wait.
}
