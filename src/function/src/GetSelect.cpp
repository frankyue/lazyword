#include "GetSelect.h"


//This function is help the soft know what user had select the degree! 
int GetSelect::Select(bool strange, bool understand, bool master, bool all)
//Instruction all = 4 ,strange = 1 , understand = 2 , master = 3
//return  1 , 2 , 3 , 4 , 5=3+2=5-4, 6=3+1=6-4 ,7=2+1=7-4
{	
	//if( show_AllBox->isChecked() )
	if( all )
	{
		//FS = 0;
		//FS = 0;
		return 4;				//select all
	}
	else
	{
		//if( show_StrangeBox->isChecked() )
		if( strange )
		{
			//if( show_UnderstandBox->isChecked() )
			if( understand )
			{
				//FS = 3;
				//IO = 1;
				return 7;		//select 1,2
			}
			else
			{
				//if( show_MasterBox->isChecked() )
				if( master )
				{
					//FS = 2;
					//IO = 1;
					return 6;		//select 1,3
				}
				else
				{
					//FS = 1;
					//IO = 0;
					return 1;		//select 1
				}
			}
		}
		else
		{
			//if( show_UnderstandBox->isChecked() )
			if( understand )
			{
				//if( show_MasterBox->isChecked() )
				if( master )
				{
					//FS = 1;
					//IO = 1;
					return 5;		//select 2,3
				}
				else
				{
					//FS = 2;
					//IO = 0;
					return 2;		//select 2					
				}
			}
			else
			{
					//FS = 3;
					//IO = 0;
					return 3;		//select 3			
			}
		}
	}
}	
