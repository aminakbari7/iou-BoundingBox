#include <glib.h>
#include <stdio.h>
#include <stdbool.h>
typedef struct {
int x, y, width, height;
} BoundingBox;
typedef struct {
int x, y, width, height;
} ROI;


int max(int a, int b){if(a>b)return a;return b;}
int min(int a, int b){if(a<b)return a;return b;}


float IOU(BoundingBox *b, ROI r) {
    int wi=(min((b->x+b->width),abs((r.x+r.width))-max(b->x,r.x)));
    int hi=(min((b->y+b->height),abs((r.y+r.height))-max(b->y,r.y)));
    if(wi<=0 || hi<=0)return -1;
    float I=wi*hi;
    float u=(b->width*b->height)+(r.width*r.height)-I;
    return I/u;   
}


int main(int argc, char *argv[]) {

ROI roi = {20, 20, 120, 120};

GList *boxes = NULL;
boxes = g_list_append(boxes,(int[]){0, 0, 30, 30});
boxes = g_list_append(boxes,(int[]){10, 10, 30, 30});
boxes = g_list_append(boxes,(int[]){20, 20, 30, 30});
boxes = g_list_append(boxes,(int[]){30, 30, 30, 30});
boxes = g_list_append(boxes,(int[]){40, 40, 30, 30});
boxes = g_list_append(boxes,(int[]){60, 60, 30, 30});
boxes = g_list_append(boxes,(int[]){80, 80, 30,30});
boxes = g_list_append(boxes,(int[]){100, 100, 30,30});
boxes = g_list_append(boxes,(int[]){120, 120, 30,30});
boxes = g_list_append(boxes,(int[]){140, 140, 30,30});

GList *node =g_list_first(boxes) ;
bool key=false;
while(node)
{
  BoundingBox* b=node->data;
  float result=IOU(b,roi);
  if(result>=0.5)
  {
     printf("{%d,%d,%d,%d}   iou=%0.2f \n",b->x,b->y,b->width,b->height,result);
     key=true;
   }  
    if(result<=0.3 && key==true)
  {
     printf("{%d,%d,%d,%d}   iou=%0.2f \n",b->x,b->y,b->width,b->height,result);
     key=false;
   } 
     
  node=node->next;
}

g_list_free(boxes);
return 0;
}
