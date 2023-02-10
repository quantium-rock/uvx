

void main()
{
	if(!zInit(2,sizeof(int))) return quit("Can't initialize process!"); 
	int* Info = (int*)zData(2);
	*Info = 35;

}