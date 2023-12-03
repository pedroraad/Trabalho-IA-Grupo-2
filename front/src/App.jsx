import { useEffect, useState } from "react";
import "./App.css";
import bfsData from "./resultBFS.json";
import dfsData from "./resultDFS.json";
import greedyData from "./resultGreedy.json";
import backtrackingData from "./resultbacktracking.json";
import Chessboard from "./Chessboard";

const dataByAlgorithm = {
  0: {
    data: bfsData,
    title: "Busca em Profundidade",
  },
  1: {
    data: dfsData,
    title: "Busca em Largura",
  },
  2: {
    data: backtrackingData,
    title: "Backtracking",
  },
  3: {
    data: greedyData,
    title: "Busca Gulosa",
  },
};

const App = () => {
  const [visibleMoviments, setVisibleMoviments] = useState([0]);
  const [index, setIndex] = useState(0);
  const [algorithm, setAlgorithm] = useState(0);
  const [currentBoardState, setCurrentBoardState] = useState();
  const [boardOrder, setBoardOrder] = useState(5);

  const resetState = () => {
    setIndex(0);
    const newVisibleMoviments = [0];

    const newState = dataByAlgorithm[algorithm].data.data.map((value) => {
      if (newVisibleMoviments.includes(value)) {
        return value;
      }

      return -1;
    });

    setVisibleMoviments(newVisibleMoviments);
    setBoardOrder(dataByAlgorithm[algorithm].data.boardOrder);
    setCurrentBoardState(newState);
  };

  const handleNewBoardState = () => {
    setIndex((prevState) => prevState + 1);
    const newVisibleMoviments = [...visibleMoviments, index + 1];

    const newState = dataByAlgorithm[algorithm].data.data.map((value) => {
      if (newVisibleMoviments.includes(value)) {
        return value;
      }

      return -1;
    });

    setVisibleMoviments(newVisibleMoviments);
    setBoardOrder(dataByAlgorithm[algorithm].data.boardOrder);
    setCurrentBoardState(newState);
  };

  const changeAlgorithm = () => {
    if (algorithm == 3) setAlgorithm(0);
    else setAlgorithm((prevState) => prevState + 1);
  };

  useEffect(() => {
    setCurrentBoardState(handleNewBoardState(0));
  }, []);

  useEffect(() => {
    resetState();
  }, [algorithm]);

  return (
    <div>
      <h1>{dataByAlgorithm[algorithm].title}</h1>
      <Chessboard boardState={currentBoardState} boardOrder={boardOrder} />
      <button onClick={handleNewBoardState}>Proximo Estado</button>
      <button onClick={changeAlgorithm}> Mudar algoritmo </button>
    </div>
  );
};

export default App;
