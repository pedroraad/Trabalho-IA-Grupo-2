import { useEffect, useState } from "react";
import "./App.css";
import bfsData from "./resultBFS.json";
import dfsData from "./resultDFS.json";
import Chessboard from "./Chessboard";

const dataByAlgorithm = {
  bfs: bfsData,
  dfs: dfsData,
};

const App = () => {
  const [index, setIndex] = useState(0);
  const [algorithm, setAlgorithm] = useState("bfs");
  const [currentBoardState, setCurrentBoardState] = useState();

  const createBasicState = () => {
    const board = [];

    const currentState = dataByAlgorithm[algorithm][`${index}`];

    for (let i = 0; i < currentState.length; i++) {
      board.push(currentState[i]);
    }

    return board;
  };

  const resetState = () => {
    const board = [];

    const currentState = dataByAlgorithm[algorithm][0];

    for (let i = 0; i < currentState.length; i++) {
      board.push(currentState[i]);
    }

    setIndex(1);
    setCurrentBoardState(board);
  };

  const handleNewBoardState = () => {
    setIndex((prevState) => prevState + 1);
    setCurrentBoardState(createBasicState());
  };

  const changeAlgorithm = () => {
    if (algorithm === "bfs") setAlgorithm("dfs");
    else setAlgorithm("bfs");
  };

  useEffect(() => {
    setCurrentBoardState(createBasicState());
  }, []);

  useEffect(() => {
    resetState();
  }, [algorithm]);

  return (
    <div>
      <h1>
        {algorithm === "bfs" ? "Busca em Largura " : "Busca em Profundidade"}
      </h1>
      <Chessboard boardState={currentBoardState} />
      <button onClick={handleNewBoardState}>Proximo Estado</button>
      <button onClick={changeAlgorithm}> Mudar algoritmo </button>
    </div>
  );
};

export default App;
