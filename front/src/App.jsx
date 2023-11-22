import  { useEffect, useState } from "react";
import "./App.css";
import tableState from './result.json';
import Chessboard from "./Chessboard";

const App = () => {
  const [currentBoardState, setCurrentBoardState] =
    useState();

  const createBasicState = () => {
    const board = [];

    for(let i = 0 ; i < 5 ; i++){
      board[i] = [];

      for(let j = 0 ; j < 5 ; j ++){
        board[i].push(tableState[i][j]);
      }
    }

    return board;
  }

  const handleNewBoardState = () => {
    setCurrentBoardState(createBasicState());
  };

  useEffect(() => {
    setCurrentBoardState(createBasicState());
  },[])

  return (
    <div>
      <Chessboard boardState={currentBoardState} />
      <button onClick={handleNewBoardState}>Novo Estado</button>
    </div>
  );
};

export default App;
