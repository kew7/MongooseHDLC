CString FileName1,FileName2,strTemp;

   if(NumFile==1000) NumFile=0;
   strTemp.Format("%d",NumFile++);
   switch(3-strTemp.GetLength())
   {
      case 2: strTemp="00"  + strTemp; break;
      case 1: strTemp="0"   + strTemp; break;
   }
