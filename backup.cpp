	CloseSocket("Closed!");
	m_pWnd->TSL.RemoveAt(m_posTSL);


		POSITION pos=AddrBook.GetHeadPosition();
	while(pos){
		CABItem * abi=(CABItem*)AddrBook.GetNext(pos);
		if(!pSock->m_sIP.Compare(abi->IP)){
			if(abi->bWelMsg)
				wm=abi->WelMsg;
			if(abi->bLvWord)
				am=abi->LvWord;
			break;
		}
	}