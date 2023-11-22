import { useEffect, useState } from "react";
import "./App.css";
import tableState from "./resultDFS.json";
import Chessboard from "./Chessboard";

const App = () => {
  const [index, setIndex] = useState(0);
  const [currentBoardState, setCurrentBoardState] = useState();

  const createBasicState = () => {
    const board = [];

    const currentState = tableState[`${index}`];

    for (let i = 0; i < currentState.length; i++) {
      board.push(currentState[i]);
    }

    return board;
  };

  const handleNewBoardState = () => {
    setIndex((prevState) => prevState + 1);
    setCurrentBoardState(createBasicState());
  };

  useEffect(() => {
    setCurrentBoardState(createBasicState());
  }, []);

  return (
    <div>
      <h1>
        Busca em Profundidade
      </h1>
      <Chessboard boardState={currentBoardState} />
      <button onClick={handleNewBoardState}>Proximo Estado</button>
    </div>
  );
};

export default App;
