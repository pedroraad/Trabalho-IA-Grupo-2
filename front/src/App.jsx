import { BrowserRouter as Router, Route, Routes  } from "react-router-dom";
import Bfs from "./BreadthFirstSearch";
import Dfs from './DepthFirstSearch';

const App = () => {
  return (
    <Router>
      <Routes>
        <Route exact path="/" Component={Bfs} />
        <Route exact path="/dfs" Component={Dfs} />
      </Routes>
    </Router>
  );
};

export default App;
